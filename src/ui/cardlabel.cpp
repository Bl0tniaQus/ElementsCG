#include "cardlabel.h"
CardLabel::CardLabel()
{
    this->card = nullptr;
}
void CardLabel::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    if (image)
    {
       QString imgName = QString::fromStdString(std::string(":/")+card->getCardName()->getImage());
       QPixmap pm(imgName);
       QString text = QString::fromStdString(card->getCardText());
       QString name = QString::fromStdString(card->getName());
       QString color = "black";
       QString TL,TR,BL,BR;
       std::string attribute = card->getElement();
       if (attribute=="Earth")
       {
        color = "#854500";
       }
       else if (attribute == "Air")
       {
        color = "green";
       }
       else if (attribute == "Light")
       {
        color = "yellow";
       }
       else if (attribute == "Dark")
       {
        color = "purple";
       }
       else if (attribute == "Fire")
       {
        color = "red";
       }
       else if (attribute == "Air")
       {
        color = "blue";
       }

       char type = card->getCardType();
       if (type==0) //spell
        {
           TL = "Cost: "+QString::number(card->getCost());
           TR = "";
           BL = "";
           BR = "";
        }
      if (type==1) //minion
        {
           TL = "Cost: "+QString::number(card->getCost());
           TR = "Lv: "+QString::number(card->getCardName()->getLevel());
           BL = "Atk: "+QString::number(card->getCardName()->getAttack());
           BR = "Def: "+QString::number(card->getCardName()->getDefence());
        }
        if (type==2) //sp minion
        {
           TL = "";
           TR = "Lv: "+QString::number(card->getCardName()->getLevel());
           BL = "Atk: "+QString::number(card->getCardName()->getAttack());
           BR = "Def: "+QString::number(card->getCardName()->getDefence());
        }

       this->ui->cardHighlight->setPixmap(pm);
       this->ui->cardHighlight->setScaledContents(true);
       this->ui->cardText->setText(text);
       this->ui->cardName->setText(name);
       this->ui->leftPanel->setStyleSheet("border: 7px solid "+color+";");
       this->ui->cardHighlight->setStyleSheet("border: 5px dashed "+color+";");
       this->ui->cardTextFrame->setStyleSheet("border: 5px dashed "+color+";");
       this->ui->cardTextTL->setText(TL);
       this->ui->cardTextBL->setText(BL);
       this->ui->cardTextT->setText(QString::fromStdString(attribute));
       this->ui->cardTextTR->setText(TR);
       this->ui->cardTextBR->setText(BR);
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


