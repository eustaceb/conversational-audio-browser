#include "helpers.h"

#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

Helpers::Helpers()
{

}

Transcription Helpers::parseTranscript(const QString &fileName)
{
    QFile *file = new QFile(fileName);
    QXmlStreamReader xml(file);

    Transcription result;
    Section currentSection;

    if (file->open(QIODevice::ReadOnly)) {
        while (!xml.atEnd() && !xml.hasError()) {
            xml.readNext();
            QString tag = xml.name().toString();
            if (xml.isStartElement()) {
                if (tag == "Turn") {
                    // <Turn endTime="5.056" speaker="spk5" startTime="4.094">
                    Turn t;
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "speaker") t.setSpeaker(val);
                        else if (val == "startTime") t.setStartTime(val);
                        else if (val == "endTime") t.setEndTime(val);
                    }
                    currentSection.addTurn(t);
                }
                else if (tag == "Section") {
                    // <Section endTime="1269.188" startTime="1266.844" topic="to14" type="report">
                    currentSection = Section();
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "topic") currentSection.setTopic(val);
                        else if (val == "startTime") currentSection.setStartTime(val);
                        else if (val == "endTime") currentSection.setEndTime(val);
                    }
                }
                else if (tag == "Topic") {
                    // <Topic desc="chocolate" id="to13" />
                    Topic t;
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "desc") t.setDesc(val);
                        else if (key == "id") t.setId(val);
                    }
                    result.addTopic(t);
                } else if (tag == "Speaker") {
                    // <Speaker accent="" check="no" dialect="native" id="spk7" name="filler_r" scope="local" type="unknown" />
                    Speaker s;
                    for (int i = 0; i < xml.attributes().length(); i++) {
                        QString key = xml.attributes()[i].name().toString();
                        QString val = xml.attributes()[i].value().toString();

                        if (key == "name") s.setName(val);
                        else if (key == "id") s.setId(val);
                    }
                    result.addSpeaker(s);
                }
            } else if (xml.isEndElement()) {
                if (tag == "Section") {
                    qInfo() << "This section had turns: " << currentSection.getTurns().size();
                    result.addSection(currentSection);
                    //currentSection = NULL;
                }
            }
            else if (xml.hasError()) {
                qInfo() << "XML error: " << xml.errorString() << endl;
            }
            else if (xml.atEnd()) {
                qInfo() << "Reached end, done" << endl;
            }
        }
    }
    qInfo() << "No of topics: " << result.getTopics().size();
    qInfo() << "No of speakers: " << result.getSpeakers().size();
    qInfo() << "No of sections: " << result.getSections().size();

    file->close();
    qInfo() << "Here we are";
    delete file;
    qInfo() << "Are we even here?";
    return result;
}
