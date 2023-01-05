#ifndef PET_H
#define PET_H

class Pet {

public:
    String name;
    int hunger = 5;
    int joy = 5;
    int sad = 0;
    int counter = 0;
    int placement = 0;
    // Food foodInventory[5];

    Pet(String enteredName);

    // draw slime - 1bottL 2bottR 3center
    void drawSlime(int location);

    // HOW MOVED IN MINIGAME
    void moveSlime(int moved);

    // Following methods will occur in certain time intervals.
    // Joy will deplete for as long as no activities are done
    void depleteStats();

    //Increments Joy and Hunger by given values
    void incrementStats(int addJoy, int addHunger);
};

#endif //PET_H