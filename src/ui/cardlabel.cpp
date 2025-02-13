#include "cardlabel.h"

CardLabel::CardLabel()
{
    this->card = nullptr;
    this->setCursor(Qt::PointingHandCursor);
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
       QString background = "";
       QString TL,TR,BL,BR;
       std::string attribute = card->getElement();
       if (attribute=="Earth")
       {
        color = "#854500";
        background = "backgroundearth";
       }
       else if (attribute == "Air")
       {
        color = "green";
        background = "backgroundair";
       }
       else if (attribute == "Light")
       {
        color = "#d2d24a";
        background = "backgroundlight";
       }
       else if (attribute == "Dark")
       {
        color = "#713e71";
        background = "backgrounddark";
       }
       else if (attribute == "Fire")
       {
        color = "#d03d3d";
        background = "backgroundfire";
       }
       else if (attribute == "Water")
       {
        color = "#469dfa";
        background = "backgroundwater";
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
       this->ui->leftPanel->setStyleSheet("border: 10px solid "+color+"; border-radius:20px; background-image:url(://"+background+");");
       this->ui->cardHighlight->setStyleSheet("border:none; background:none;");
       this->ui->cardTextFrame->setStyleSheet("border:none; background:none;");
       this->ui->cardTextTL->setText(TL);
       this->ui->cardTextTL->setStyleSheet("background:none;");
       this->ui->cardTextBL->setText(BL);
       this->ui->cardTextT->setText(QString::fromStdString(attribute));
       this->ui->cardText->setStyleSheet("border:none; border-radius: 0px; border-top: 3px solid "+color+"; border-bottom: 3px solid "+color+"; padding-top:4px; background:none;");
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


