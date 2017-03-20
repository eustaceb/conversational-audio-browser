#include "helpers.h"
#include "data-models/transcription.h"
#include "data-models/section.h"
#include "data-models/turn.h"
#include "data-models/speaker.h"
#include "data-models/topic.h"


Transcription* Helpers::parseTranscript(QIODevice *source)
{
    QXmlStreamReader xml(source);
    if (!source->open(QIODevice::ReadOnly)) return 0;

    Transcription *result = new Transcription(source->objectName());
    Section *currentSection;

    QMap<QString, Topic*> topicMap;
    QMap<QString, Speaker*> speakerMap;

    // Create none speaker as some turns have no speaker
    Speaker *none = new Speaker("", "None");
    speakerMap.insert(none->getId(), none);
    result->addSpeaker(none);

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        QString tag = xml.name().toString();
        if (xml.isStartElement()) {
            if (tag == "Turn") {
                // <Turn endTime="5.056" speaker="spk5" startTime="4.094">
                qreal endTime, startTime;
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
                    Turn *t = new Turn(startTime, endTime, s);
                    s->addTurn(t);
                    currentSection->addTurn(t);
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
//    QStringList splitFilename = source->objectName().split("/");
//    qInfo() << "Transcription" << splitFilename.at(splitFilename.length() - 1) << "loaded.";

    source->close();
    return result;
}

int Helpers::exportStdItemModelToCsv(const QString &filename, QStandardItemModel *model, bool headers)
{
    qInfo() << "Writing to " << filename;
    QFile f(filename);
    if (f.open(QIODevice::WriteOnly)) {
        QTextStream out(&f);
        if (headers) {
            for (int i = 0; i < model->columnCount(); i++) {
                out << model->headerData(i, Qt::Orientation::Horizontal).toString() << ",";
            }
            out << endl;
        }
        for (int i = 0; i < model->rowCount(); i++) {
            for (int j = 0; j < model->columnCount(); j++) {
                QString data = model->data(model->index(i, j)).toString();
                if (data.contains(",") || data.contains("\""))
                    data = "\"" + data + "\"";
                out << data;
                if (j != model->columnCount() - 1)
                    out << ",";
            }
            out << endl;
        }
    } else {
        return -1;
    }
    f.close();
    return 1;
}
