#include "cardlabel.h"

void CardLabel::setCard(const char* c)
{
    this->cardName = new char[strlen(c)+1];
    strcpy(this->cardName, c);
}
void CardLabel::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    QString imgName = QString::fromStdString(std::string(":/")+std::string(this->cardName)+std::string("_card"));
    QPixmap pm(imgName);
    this->ui->cardHighlight->setPixmap(pm);
    this->ui->cardHighlight->setScaledContents(true);
}
void CardLabel::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    emit handCardHighlight(this->id);
}
CardLabel::~CardLabel()
{
    delete[] this->cardName;
}


