#include "cardlabel.h"
CardLabel::CardLabel()
{
    this->cardName = new char[0];
}

void CardLabel::setCard(const char* c)
{
    delete[] this->cardName;
    this->cardName = new char[strlen(c)+1];
    strcpy(this->cardName, c);
}
void CardLabel::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    if (image)
    {
       QString imgName = QString::fromStdString(std::string(":/")+std::string(this->cardName)+std::string("_card"));
        QPixmap pm(imgName);
        this->ui->cardHighlight->setPixmap(pm);
        this->ui->cardHighlight->setScaledContents(true);
    }

}
void CardLabel::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    if (this->place==1) {emit handCardHighlight(this->id);}
    if (this->place==5) {emit targetCardHighlight(this->id);}
    if (this->place==4) {emit specialDeckCardHighlight(this->id);}
}
CardLabel::~CardLabel()
{
    delete[] this->cardName;
}


