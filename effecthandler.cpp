#include "effecthandler.h"
#include "globals.h"
EffectHandler::EffectHandler()
{

}
void EffectHandler::onSpell(Card* card)
{
short id = card->getCardId();
switch (id)
{
if (id==4)
{
selectFieldTarget();
}
}
}
