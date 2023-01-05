#include "Food.h"

class Food {

  Food(String foodGained, int nutritionGained){
  	type = foodGained;
    nutrition = nutritionGained;
    countRewards++;
  
  }
  
  
  void setFoodSprite() {
    if (type == "cookie") {
      copyArray(cookieSprite);
    } else if (type == "balloon") {
      copyArray(balloonSprite);
    }  
  }
  
  void copyArray(byte copyFrom[]){
    for (int i = 0; i < 8; i++) {
      foodSpriteArray[i] = copyFrom[i];
    
    }
    lcd_1.createChar(4, foodSpriteArray);
  }
  
  void printFood() {
  	lcd_1.setCursor(0,2);
    lcd_1.write(4);
    
  
  
  }
  



};