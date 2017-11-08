#include "player.h"
#include "game.h"
#include <QDebug>
extern Game *game;

Player::Player(QGraphicsItem *parent){

    //set graphic
    setPixmap(QPixmap(":/images/text.png"));
    health = 5;
    strength = 2;
}

void Player::checkAction(Button *button)
{
    if(button->getName() == "exit"){
        exit(0);
    }else if(button->getName() == "down"){
        goRoom("south");
    }else if(button->getName() == "left"){
        goRoom("west");
    }else if(button->getName() == "right"){
        goRoom("east");
    }else if(button->getName() == "up"){
        goRoom("north");
    }else if(button->getName() == "inventory"){
        inven = new Inventory();
    }else if(button->getName() == "exitInventory"){
        delete inven;
    }else if(button->getName() == "medicine"){
        if(myItem.size() > 5){
            writeDiary("I can't take more, that's too heavy");

         }else{
            Item *medicine = new Item("medicine", "good medicine", ":/images/medicine.png");
            game->currentRoom->removeItem(medicine);
            delete medicine;
            Item *medicine1 = new Item("Medicine", "good medicine", ":/images/medicine.png");
            addItem(medicine1);

            if(game->item1->getName() == "medicine"){
                game->item1->setPixmap(QString::fromStdString(""));
                game->item1->setName("");
            }else{
                game->item2->setPixmap(QString::fromStdString(""));
                game->item2->setName("");
            }
        }
    }else if(button->getName() == "arm"){
        if(myItem.size() > 5){
            writeDiary("I can't take more, that's too heavy");
         }else{
            Item *arm = new Item("arm", "good arm", ":/images/arm.png");
            game->currentRoom->removeItem(arm);
            delete arm;
            Item *arm1 = new Item("Arm", "good arm", ":/images/arm.png");
            addItem(arm1);
            if(game->item1->getName() == "arm"){
                game->item1->setPixmap(QString::fromStdString(""));
                game->item1->setName("");
            }else{
                game->item2->setPixmap(QString::fromStdString(""));
                game->item2->setName("");
            }
        }

    }else if(button->getName() == "teleportation"){
        if(myItem.size() > 5){
            writeDiary("I can't take more, that's too heavy");
         }else{
            Item *teleportation = new Item("teleportation", "teleportation", ":/images/teleportation.png");
            game->currentRoom->removeItem(teleportation);
            delete teleportation;
            Item *teleportation1 = new Item("Teleportation", "teleportation", ":/images/teleportation.png");
            addItem(teleportation1);
            if(game->item1->getName() == "teleportation"){
                game->item1->setPixmap(QString::fromStdString(""));
                game->item1->setName("");
            }else{
                game->item2->setPixmap(QString::fromStdString(""));
                game->item2->setName("");
            }
        }
    }else if(button->getName() == "Teleportation"){
        Item *teleportation = new Item("Teleportation", "teleportation", ":/images/teleportation.png");
        useItem(teleportation);
        delete teleportation;
        inven->showMyItems();
    }else if(button->getName() == "Medicine"){
        Item *medicine = new Item("Medicine", "good medicine", ":/images/medicine.png");
        useItem(medicine);
        delete medicine;
        inven->showMyItems();
    }else if(button->getName() == "Arm"){
        Item *arm = new Item("Arm", "good arm", ":/images/arm.png");
        useItem(arm);
        delete arm;
        inven->showMyItems();
    }else if(button->getName() == "enemy"){
        if(!attack(game->currentRoom->getCurrentEnemy())){
            game->health->setPlainText(QString("health: ") + QString::number(0));
            Final *final = new Final(":/images/lose.png");
        }else{
            if(game->currentRoom->getCurrentEnemy()->returnBoss()){
                   Final *final = new Final(":/images/win.png");
            }
            game->currentRoom->killEnemy();
            game->health->setPlainText(QString("health: ") + QString::number(health));
            writeDiary("Thanks God, I survived.");
        }
    }
}

void Player::writeDiary(string sentence)
{
    game->myDiary->setText(game->myDiary->text() +"\n"+ QString::fromStdString(sentence));
}

void Player::clearDiary()
{
    game->myDiary->setText("");
}

void Player::goRoom(string direction)
{
    string message[] = {"It seems like there are somethings\non the table.",
                       "Look! What's that under the floor.",
                       "Inside the vase was something\nflashing."};

    string noDoor[] ={"I hate to look at myself inside\nmirror.",
                      "I can't see clearly if there is\nanything outside the window.",
                      "Fine, I'll try another way."};

    srand((unsigned)time(NULL));
    int random = (rand() % 3);
    // Try to leave current room.
    Room *nextRoom = game->currentRoom->nextRoom(direction);
    if (nextRoom == NULL){
        writeDiary(noDoor[random]);
    }else{
        clearDiary();
        game->currentRoom = nextRoom;
        writeDiary(game->currentRoom->longDescription());
        if(game->currentRoom->showCurrentItems()){
            writeDiary(message[random]);
        }
        if(game->currentRoom->isEnemy()){
            writeDiary("But...Jesus, what's that ?");
        }
    }
}

void Player::addItem(Item *item)
{
    myItem.push_back(*item);

}

void Player::useItem(Item *itemUsed)
{

   for(int i = 0; i < myItem.size(); i++){
      if(myItem[i].getShortDescription() == itemUsed->getShortDescription())
      {
          if(myItem[i].getShortDescription() == "Medicine"){
              game->health->setPlainText(QString("health: ") + QString::number(++health));
          }else if(myItem[i].getShortDescription() == "Arm"){
              game->strength->setPlainText(QString("strength: ") + QString::number(++strength));
          }else if(myItem[i].getShortDescription() == "Teleportation"){
              Room *total[] = {game->a, game->b, game->c, game->d, game->e, game->f, game->g,
                                game->h, game->i};
              srand((unsigned)time(NULL));
              int random = (rand() % 9);
              game->currentRoom = total[random];
              clearDiary();
              writeDiary(game->currentRoom->longDescription());
              if(game->currentRoom->showCurrentItems()){
                  writeDiary("It seems like there are somethings\non the table.");
              }
          }
          myItem.erase(myItem.begin() + i);
          i--;
          break;
      }
   }
}

bool Player::attack(Enemy *enemy)
{
    int enemyHealth = enemy->getHealth();
    int enemyStrength = enemy->getStrength();
    while(true){
        enemyHealth -= strength;
        health -= enemyStrength;
        if(enemyHealth <= 0){
            return true;
        }else if(health <= 0){
            return false;
        }
    }
}

vector<Item> *Player::myitemList()
{
    return &myItem;
}


int Player::getHealth()
{
    return health;
}

int Player::getStrength()
{
    return strength;
}

