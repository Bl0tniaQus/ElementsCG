#include "cardlabel.h"
CardLabel::CardLabel()
{
    this->card = nullptr;
}
void CardLabel::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    if (image)
    {
       QString imgName = QString::fromStdString(std::string(":/")+std::string(card->getCardName()->getImage()));
       QPixmap pm(imgName);
       QString text = QString(card->getCardText());
       this->ui->cardHighlight->setPixmap(pm);
       this->ui->cardHighlight->setScaledContents(true);
       this->ui->cardText->setText(text);
       this->ui->cardText->setScaledContents(true);
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

}


