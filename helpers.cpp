#include "helpers.h"

Helpers::Helpers()
{

}

SelectionTreeModel* Helpers::generateSelectionTree(Transcription *t)
{
    // Setup headers
    QList<QVariant> heading;
    heading.append("Name");
    heading.append("Type");
    heading.append("Description");

    SelectableTreeItem *root = new SelectableTreeItem(heading);

    foreach (Topic *topic, t->getTopics()) {
        SelectableTreeItem *topicItem = new SelectableTreeItem(topic, root);
        foreach (Section *section, topic->getSections()) {
            SelectableTreeItem *sectionItem = new SelectableTreeItem(section, topicItem);
            foreach (Turn *turn, section->getTurns()) {
                sectionItem->appendChild(new SelectableTreeItem(turn, sectionItem));
            }
            topicItem->appendChild(sectionItem);
        }
        root->appendChild(topicItem);
    }

    return new SelectionTreeModel(root);
}

Transcription* Helpers::parseTranscript(const QString &fileName)
{
    // TODO: Exceptions in case of ill-formatted XML
    QFile *file = new QFile(fileName);
    QXmlStreamReader xml(file);

    Transcription *result = new Transcription();
    Section *currentSection;

    QMap<QString, Topic*> topicMap;
    QMap<QString, Speaker*> speakerMap;

    Speaker *none = new Speaker("", "None");
    speakerMap.insert(none->getId(), none);
    result->addSpeaker(none);

    if (file->open(QIODevice::ReadOnly)) {
        while (!xml.atEnd() && !xml.hasError()) {
            xml.readNext();
            QString tag = xml.name().toString();
            if (xml.isStartElement()) {
                if (tag == "Turn") {
                    // <Turn endTime="5.056" speaker="spk5" startTime="4.094">
                    double endTime, startTime;
                    QList<Speaker*> speakers;
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "speaker") {
                            foreach (const QString &spkr, val.split(" ")) {
                                speakers.append(speakerMap.find(spkr).value());
                            }
                        }
                        else if (key == "startTime") startTime = val.toDouble();
                        else if (key == "endTime") endTime = val.toDouble();
                    }
                    // If there are multiple speakers - create separate turns for them
                    foreach (Speaker *s, speakers) {
                        currentSection->addTurn(new Turn(startTime, endTime, s));
                    }
                }
                else if (tag == "Section") {
                    // <Section endTime="1269.188" startTime="1266.844" topic="to14" type="report">
                    currentSection = new Section();
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "topic") {
                            Topic *t = topicMap.find(val).value();
                            currentSection->setTopic(t);
                            t->addSection(currentSection);
                        }
                        else if (key == "startTime") currentSection->setStartTime(val.toDouble());
                        else if (key == "endTime") currentSection->setEndTime(val.toDouble());
                    }
                }
                else if (tag == "Topic") {
                    // <Topic desc="chocolate" id="to13" />
                    Topic *t = new Topic();
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "desc") t->setDesc(val);
                        else if (key == "id") t->setId(val);
                    }
                    topicMap.insert(t->getId(), t);
                    result->addTopic(t);
                } else if (tag == "Speaker") {
                    // <Speaker accent="" check="no" dialect="native" id="spk7" name="filler_r" scope="local" type="unknown" />
                    Speaker *s = new Speaker();
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "name") s->setName(val);
                        else if (key == "id") s->setId(val);
                    }
                    speakerMap.insert(s->getId(), s);
                    result->addSpeaker(s);
                }
            }
            else if (xml.hasError()) {
                qInfo() << "XML error: " << xml.errorString() << endl;
            }
            else if (xml.atEnd()) {
                qInfo() << "Parsing complete";
            }
        }
    }
    qInfo() << "No of topics: " << result->getTopics().size();
    qInfo() << "No of speakers: " << result->getSpeakers().size();

    file->close();
    delete file;
    return result;
}
