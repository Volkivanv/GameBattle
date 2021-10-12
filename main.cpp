#include <iostream>
#include <vector>
#include <string>
#include <ctime>
//#include <cstdlib>
//#include <conio.h>

struct player{
    std::string name;
    int x = 20;
    int y = 20;
    int life;
    int armor;
    int drop;
};

void initPlayer(player& somePlayer, std::string someName){
    somePlayer.name = someName;
    somePlayer.x = rand() % 40;
    somePlayer.y = rand() % 40;
    somePlayer.life = 50 + rand()%100;
    somePlayer.armor = rand()%50;
    somePlayer.drop = 15 + rand()%15;
}
void floodVec(std::vector<player>& enemies){
    for(int i = 0; i < enemies.size(); i++){
        initPlayer(enemies[i],"Enemy#"+ std::to_string(i));
    }
}

void moveEnemy(player& somePlayer){

    int hv = rand()%2;

    if(hv == 0) {
        int deltaX = rand() % 3 - 1;
        if ((somePlayer.x + deltaX) > 0 && (somePlayer.x + deltaX) < 40) {
            somePlayer.x += deltaX;
        } else {
            somePlayer.x -= deltaX;
        }
    } else {
        int deltaY = rand() % 3 - 1;
        if ((somePlayer.y + deltaY) > 0 && (somePlayer.y + deltaY) < 40) {
            somePlayer.y += deltaY;
        } else {
            somePlayer.y -= deltaY;
        }
    }
}
void movePlayer(player& somePlayer, char key){
    switch (key){
        case 'a':
            if(somePlayer.x-1 >= 0) somePlayer.x-=1;
            break;
        case 'd':
            if(somePlayer.x+1 < 40) somePlayer.x+=1;
            break;
        case 'w':
            if(somePlayer.y-1 >= 0) somePlayer.y-=1;
            break;
        case 's':
            if(somePlayer.y+1 < 40) somePlayer.y+=1;
            break;
    }

}

void moveEnemies(std::vector<player>& enemies){
    for(auto & enemy : enemies){
        moveEnemy(enemy);
    }

}

char mark(std::vector<player>& enemies, player& p, int r, int c){
    if(p.x == c && p.y == r) return 'P';

    for(int i = 0; i < enemies.size(); i++){
        //if(enemies[i].x == c && enemies[i].y == r) return 'E';
        if((enemies[i].x == c && enemies[i].y == r) && (enemies[i].life > 0)) return i+'0';
    }
    return '.';
}

void showScreen(std::vector<player>& enemies, player& p){
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            std::cout << mark(enemies, p, i, j)<<" ";
        }
        std::cout << std::endl;
    }

}

void showStatus(std::vector<player>& enemies, player& p){
    for(int i = 0; i < enemies.size(); i++){
        std::cout << enemies[i].name <<" life: "<< enemies[i].life <<"; armor: " << enemies[i].armor <<
        "; drop: " << enemies[i].drop <<" .";
        if(enemies[i].life <= 0) std::cout << "Enemy is killed!!!";
        std::cout << std::endl;
    }
    std::cout << p.name <<" life: "<< p.life <<"; armor: " << p.armor << "; drop: " << p.drop << std::endl;
        if(p.life <= 0) std::cout << "Player is killed!!!";
        std::cout << std::endl;

}

void hit(player& p, player& e){
    if(e.armor >= p.drop){
        e.armor -=p.drop;
    } else {
        e.life =e.life - (p.drop-e.armor);
        e.armor = 0;
    }
    if(e.life < 0) e.life = 0;
}

void enemiesHit(std::vector<player>& enemies, player& p){
    for(int i = 0; i < enemies.size();i++){
        if((enemies[i].x == p.x)&&(enemies[i].y == p.y)) hit(enemies[i],p);
    }
}

void playerHit(std::vector<player>& enemies, player& p){
    for(int i = 0; i < enemies.size();i++){
        if((enemies[i].x == p.x)&&(enemies[i].y == p.y)) hit(p,enemies[i]);
    }
}

bool endGame(std::vector<player>& enemies, player& p){
    if (p.life <= 0) {
        std::cout << "Game over! You have lost the game!" << std::endl;
        return true;
    }
    for(int i = 0; i < enemies.size();i++){
        if(enemies[i].life > 0) return false;
    }
    std::cout << "You won!" << std::endl;
    return true;
}

int main() {
    std::srand(std::time(nullptr));
    int numEnemies;
    std::cout << "Please input count of enemies!" << std::endl;
    std::cin >> numEnemies;
    std::vector<player> enemy(numEnemies);
    player gamer;


    floodVec(enemy);
    initPlayer(gamer, "Cheburashka");
    std::cout << "Please, input name of your Player!" <<std::endl;
    std::cin >> gamer.name;
    std::cout << "Please, input life level your Player between 50 and 150!" << std::endl;
    std::cin >> gamer.life;
    std::cout << "Please, input armor level your Player between 0 and 50!" << std::endl;
    std::cin >> gamer.armor;
    std::cout << "Please, input drop level your Player between 15 and 30!" << std::endl;
    std::cin >> gamer.drop;
    showStatus(enemy,gamer);
    showScreen(enemy, gamer);
    char step;

    std::cout <<"Your move Player! Input new step a,s,w,d or e for exit" << std::endl;
    std::cin >> step;

    while(step !='e'){
        movePlayer(gamer,step);
        playerHit(enemy,gamer);
        //showScreen(enemy, gamer);
        std::cout<<"Enemie's move" << std::endl;
        moveEnemies(enemy);
        enemiesHit(enemy,gamer);

        showStatus(enemy,gamer);
        showScreen(enemy, gamer);
        //system("cls");
        if(endGame(enemy,gamer)) break;

        std::cout <<"Your move Player! Input new step a,s,w,d or e for exit" << std::endl;
        std::cin >> step;

    }


    return 0;
}
