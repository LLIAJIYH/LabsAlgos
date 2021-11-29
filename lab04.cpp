/*

    1) 22 line: change for windows to "cls"
    2) Players can kill each other in one moment
    3) Limitted amount of players [-9; -1] and [2, 9]
    4) movements are based on random in allowed ways

*/

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <string>
#include <time.h>
#include <memory>
#include <algorithm>
#include <unistd.h>

using namespace std;

#define COMMAND "clear"
// cls for windows

class Warrior
{
public:
    virtual ~Warrior() {}
    virtual char getID() const = 0;
    virtual void print() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getHP() const = 0;
    virtual int getAttack() const = 0;
    virtual int getAttackRange() const = 0;
    virtual string getName() const = 0;

    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;
    virtual void setHP(int hp) = 0;

    virtual int attack(Warrior *warrior) = 0;
};

class MeleeWarrior : public Warrior
{
protected:
    char m_id;
    int m_hp, m_attack, m_range;
    int m_x, m_y;
    string m_name;

public:
    MeleeWarrior(const MeleeWarrior &src) : MeleeWarrior(src.m_id, src.m_hp, src.m_attack, src.m_range, src.m_x, src.m_y, src.m_name) {}
    MeleeWarrior(MeleeWarrior &&) = default;
    MeleeWarrior(char id, int hp, int attack, int range, int x, int y, string name)
    {
        m_id = id;
        m_hp = hp;
        m_attack = attack;
        m_range = range;
        m_x = x;
        m_y = y;
        m_name = name;
    }

    virtual void print() const override
    {
        cout << m_name << ": " << m_hp << " " << m_attack << " (" << m_x << ", " << m_y << ") " << endl;
    }

    virtual char getID() const override { return m_id; }
    virtual int getX() const override { return m_x; }
    virtual int getY() const override { return m_y; }
    virtual int getHP() const override { return m_hp; }
    virtual int getAttack() const override { return m_attack; }
    virtual int getAttackRange() const override { return m_range; }
    virtual string getName() const override { return m_name; }

    virtual void setX(int x) override { m_x = x; }
    virtual void setY(int y) override { m_y = y; }
    virtual void setHP(int hp) override { m_hp = hp; }

    virtual int attack(Warrior *warrior) override
    {
        float dist = sqrt(pow(this->m_x - warrior->getX(), 2) + pow(this->m_y - warrior->getY(), 2));
        if (dist <= this->m_range)
        {
            warrior->setHP(warrior->getHP() - this->m_attack);
            cout << this->getName() << " attacked " << warrior->getName() << endl;
            return 0;
        }
        cout << this->m_name << " can't attack " << warrior->getName() << endl;
        return -1;
    };
};

class Archer : public Warrior
{
protected:
    char m_id;
    int m_hp, m_attack, m_range;
    int m_x, m_y;
    string m_name;

public:
    Archer(const Archer &src) : Archer(src.m_id, src.m_hp, src.m_attack, src.m_range, src.m_x, src.m_y, src.m_name) {}
    Archer(Archer &&) = default;
    Archer(char id, int hp, int attack, int range, int x, int y, string name)
    {
        m_id = id;
        m_hp = hp;
        m_attack = attack;
        m_range = range;
        m_x = x;
        m_y = y;
        m_name = name;
    }

    virtual void print() const override
    {
        cout << m_name << ": " << m_hp << " " << m_attack << " (" << m_x << ", " << m_y << ") " << endl;
    }

    virtual char getID() const override { return m_id; }
    virtual int getX() const override { return m_x; }
    virtual int getY() const override { return m_y; }
    virtual int getHP() const override { return m_hp; }
    virtual int getAttack() const override { return m_attack; }
    virtual int getAttackRange() const override { return m_range; }
    virtual string getName() const override { return m_name; }

    virtual void setX(int x) override { m_x = x; }
    virtual void setY(int y) override { m_y = y; }
    virtual void setHP(int hp) override { m_hp = hp; }
    virtual int attack(Warrior *warrior) override
    {
        float dist = sqrt(pow(this->m_x - warrior->getX(), 2) + pow(this->m_y - warrior->getY(), 2));
        if (dist <= this->m_range)
        {
            warrior->setHP(warrior->getHP() - this->m_attack);
            cout << this->getName() << " attacked " << warrior->getName() << endl;
            return 0;
        }
        cout << this->m_name << " can't attack " << warrior->getName() << endl;
        return -1;
    };
};

class Game
{
private:
    vector<Warrior *> players;
    vector<vector<char>> gamepole;
    int len;

public:
    Game(vector<Warrior *> _players, int n)
    {
        players = _players;
        this->makeField(n);
        this->setWalls();
        this->setPlayers();
        this->print();
    }

    void rotatePlayers()
    {
        rotate(players.begin(), players.begin() + 1, players.end());
    }

    void makeField(int n)
    {
        len = n;
        gamepole.resize(n);
        for (int i = 0; i < n; i++)
        {
            gamepole[i].resize(n);
        }
    }

    void setWalls()
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                int random = rand() % 10;
                if (random < 1)
                {
                    gamepole[i][j] = '#';
                }
                else
                {
                    gamepole[i][j] = '0';
                }
            }
        }
    }

    void setPlayers()
    {
        for (int i = 0; i < players.size(); i++)
        {
            int x, y;
            char id;
            x = players[i]->getX();
            y = players[i]->getY();
            gamepole[x][y] = players[i]->getID();
        }
    }

    void print()
    {
        cout << endl;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                cout << gamepole[i][j] << " ";
            }
            cout << endl;
        }
    }

    void start()
    {
        int step = 0;
        while (players.size() != 1)
        {
            rotatePlayers();
            sleep(0);
            system(COMMAND);
            print();
            cout << step << endl;
            step += 1;
            for (int i = 0; i < players.size(); ++i)
            {
                cout << players[i]->getName() << " move" << endl;
                if (rand() % 10 < 6)
                {
                    //move to allowed place
                    movePlayer(players[i]);
                }
                else
                {
                    //attack next player
                    cout << players[i]->getName() << " tries to attack" << endl;
                    if (i != players.size() - 1)
                    {
                        players[i]->attack(players[i + 1]);
                    }
                }
                if (players[i]->getHP() <= 0)
                {
                    cout << players[i]->getName() << " died" << endl;
                    gamepole[players[i]->getX()][players[i]->getY()] = '0';
                    players.erase(players.begin() + i);
                }
            }
        }
        system(COMMAND);
        print();
        cout << "Winner of this battle is" << endl;
        players[0]->print();
    }

    void movePlayer(Warrior *player)
    {
        vector<pair<int, int>> allowed_moves;
        list<pair<int, int>> all_moves = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        for (auto d : all_moves)
        {
            if (player->getX() + d.first <= len - 1 && player->getX() + d.first >= 0 && player->getY() + d.second <= len - 1 && player->getY() + d.second >= 0)
            {
                if (gamepole[player->getX() + d.first][player->getY() + d.second] == '0')
                {
                    allowed_moves.push_back(make_pair(d.first, d.second));
                }
            }
        }
        if (allowed_moves.size() > 0)
        {
            int index = rand() % allowed_moves.size();
            moveTo(player, allowed_moves[index]);
        }
    }

    void moveTo(Warrior *player, pair<int, int> move)
    {
        if (player->getX() + move.first <= len - 1 && player->getX() + move.first >= 0 && player->getY() + move.second <= len - 1 && player->getY() + move.second >= 0 && gamepole[player->getX() + move.first][player->getY() + move.second] == (char)'0')
        {
            gamepole[player->getX() + move.first][player->getY() + move.second] = player->getID();
            player->setX(player->getX() + move.first);
            player->setY(player->getY() + move.second);
            gamepole[player->getX() - move.first][player->getY() - move.second] = '0';
            cout << player->getName() << " moved by (" << player->getX() << ", " << player->getY() << ") " << endl;
        }
        else
        {
            cout << "can't move to this position" << endl;
        }
    }
};

int main()
{
    system(COMMAND);
    srand((unsigned)time(0));
    int m_id, m_hp, m_attack, m_range;
    int m_x, m_y;
    string m_name;

    MeleeWarrior *me1 = new MeleeWarrior('2', 10, 10, 1, 0, 0, (string) "warrior1");
    Archer *ar1 = new Archer('3', 10, 5, 3, 0, 3, (string) "archery1");
    MeleeWarrior *me2 = new MeleeWarrior('4', 10, 10, 1, 3, 0, (string) "warrior2");
    Archer *ar2 = new Archer('5', 10, 5, 3, 3, 3, (string) "archery2");
    MeleeWarrior *me3 = new MeleeWarrior('6', 10, 10, 1, 6, 6, (string) "warrior3");
    Archer *ar3 = new Archer('7', 10, 5, 3, 6, 9, (string) "archery3");
    MeleeWarrior *me4 = new MeleeWarrior('8', 10, 10, 1, 9, 6, (string) "warrior4");
    Archer *ar4 = new Archer('9', 10, 5, 3, 9, 9, (string) "archery4");

    vector<Warrior *> players;
    players.push_back(me1);
    players.push_back(ar1);
    players.push_back(me2);
    players.push_back(ar2);
    players.push_back(me3);
    players.push_back(ar3);
    players.push_back(me4);
    players.push_back(ar4);
    Game game(players, 10);
    game.start();
}
