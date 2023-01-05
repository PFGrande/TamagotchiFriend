#include "Pet.h"

Pet::Pet(String enteredName) {
    name = enteredName;
}

// draw slime - 1bottL 2bottR 3center
void Pet::drawSlime(int location)
{
    switch (location)
    {
    case 1:
        lcd_1.setCursor(0, 1);
        lcd_1.write(1);
        lcd_1.setCursor(1, 1);
        lcd_1.write(2);
        break;

    case 2:
        lcd_1.setCursor(14, 1);
        lcd_1.write(1);
        lcd_1.setCursor(15, 1);
        lcd_1.write(2);
        break;
    case 3:
        lcd_1.setCursor(7, 1);
        lcd_1.write(1);
        lcd_1.setCursor(8, 1);
        lcd_1.write(2);
        break;
    }
}
// HOW MOVED IN MINIGAME
void Pet::moveSlime(int moved)
{

    // relative to left side position should not go over or under these
    if (placement == 0)
    {
        moved = 0;
    }
    else if (placement == 15)
    {
        moved = 15;
    }
    lcd_1.setCursor(moved, 1);
    lcd_1.write(1);
    lcd_1.setCursor(moved + 1, 1);
    lcd_1.write(2);
}
// Following methods will occur in certain time intervals.
// Joy will deplete for as long as no activities are done
void Pet::depleteStats()
{
    counter++;
    // Serial.print(counter);
    // Serial.print(" ");
    if (counter > 100 && joy > 0 && counter < 102)
    {
        joy = joy - 1;
        lcd_1.clear(); // clears to hunger and joy maxs dont overlap
    }
    if (counter > 200 && hunger > 0 && counter < 202)
    {
        hunger = hunger - 1;
        counter = 0;
        lcd_1.clear(); // clears to hunger and joy maxs dont overlap
    }
    /*for (int i = 0; i < 15 - joy) {


    }*/
}

/*void increaseSad() {
  if(hunger < 10) {


  }
}*/

void Pet::incrementStats(int addJoy, int addHunger)
{
    joy = joy + addJoy;
    hunger = hunger + addHunger;
    if (joy > 15)
    {
        joy = 15;
    }

    if (hunger > 15)
    {
        hunger = 15;
    }
}
