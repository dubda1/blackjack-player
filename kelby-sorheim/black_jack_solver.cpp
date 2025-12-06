#include "black_jack_solver.hpp"
#include <iostream>

static chip_t totalChips;
static chip_t min;

BlackJackSolver::BlackJackSolver(
    uint64_t number_of_decks,
    float reshuffle_percentage,
    uint64_t number_of_rounds,
    chip_t chips,
    chip_t table_min,
    chip_t table_max)
{
    totalChips = chips;
    min = table_min;
}

BlackJackSolver::~BlackJackSolver() {}

chip_t BlackJackSolver::get_bet() {
    if(totalChips > min){
        return min;
    }
    return 0;
}

int BlackJackSolver::hardValue(std::span<const Card> cards){
    int value = 0;
    for (int i = 0; i < static_cast<int>(cards.size()); i++) {
        int curVal = static_cast<int>(cards[i].rank);
        if(curVal == 0){
            value += 1;
        } else if(curVal <= 4){
            value += 10;
        } else{
            value += (14 - curVal);
        }
    }
    return value;
}

int BlackJackSolver::softValue(std::span<const Card> cards){
    int value = 0;
    int sawAce = 0;
    for (int i = 0; i < static_cast<int>(cards.size()); i++) {
        int curVal = static_cast<int>(cards[i].rank);
        if(curVal == 0){
            value += 1;
            sawAce = 1;
        } else if(curVal <= 4){
            value += 10;
        } else{
            value += (14 - curVal);
        }
    }
    if(sawAce == 1 && value <= 11){
        value += 10;
    }
    return value;
}

int dealerDB;
int hardDB;
int softDB;
int count = 0;
BlackJackAction BlackJackSolver::handle_hand(
        Card dealer_up_card, 
        std::span<const Card> cards, 
        BlackJackHandStatus status)
{
    int hard = hardValue(cards);
    int soft = softValue(cards);
    bool canDD = true;
    int dealer;
    int cur = static_cast<int>(dealer_up_card.rank);
    if (cur == 0){
        dealer = 11;
    }else if (cur <= 4){
        dealer = 10;  
    }else{
        dealer = 14 - cur;  
    }
    //check for doubled:
    if(status == BlackJackHandStatus::DOUBLED || static_cast<int>(cards.size()) != 2){
        canDD = false;
    }
    dealerDB = dealer;
    hardDB = hard;
    softDB = soft;
    //perfect version ;)
    if(status == BlackJackHandStatus::NONE && static_cast<int>(cards.size()) == 2 && ((hard == 16 && dealer >= 9) || (hard == 15 && dealer == 10))){
        return BlackJackAction::SURRENDER;
    }
    if(status != BlackJackHandStatus::DOUBLED && status != BlackJackHandStatus::SPLIT && static_cast<int>(cards.size()) == 2){
        int rankOne = static_cast<int>(cards[0].rank);
        int rankTwo = static_cast<int>(cards[1].rank);
        if(rankOne == rankTwo){
            if(rankOne == 0 || rankOne == 6){
                return BlackJackAction::SPLIT;
            }
            if(rankOne == 5){
                if((dealer >= 2 && dealer <= 6) || dealer == 8 || dealer == 9){
                    return BlackJackAction::SPLIT;
                }
            }
            if(rankOne == 7 || rankOne == 11 || rankOne == 12){
                if(dealer <= 7){
                    return BlackJackAction::SPLIT;
                }
            }
            if(rankOne == 8){
                if(dealer <= 6){
                    return BlackJackAction::SPLIT;
                }
            }
            if(rankOne == 10){
                if(dealer == 5 || dealer == 6){
                    return BlackJackAction::SPLIT;
                }
            }
        }
    }
    
    if(soft > hard){
        //soft code first
        //double soft first:
        if(canDD){
            if((soft == 18 || soft == 17) && dealer >= 3 && dealer <= 6){
                return BlackJackAction::DOUBLE_DOWN;
            }
            if((soft == 16 || soft == 15) && dealer >= 4 && dealer <= 6){
                return BlackJackAction::DOUBLE_DOWN;
            }
            if((soft == 14 || soft == 13) && (dealer == 5 || dealer == 6)){
                return BlackJackAction::DOUBLE_DOWN;
            }
        }
        if(soft <= 17){
            return BlackJackAction::HIT;
        }

        //ONLY SPLIT ROW FOR SOFT BELOW
        if(soft == 18){
            if(dealer == 9 || dealer == 10 || dealer == 11){
                return BlackJackAction::HIT;
            } else{
                return BlackJackAction::STAND;
            }
        }
        if(soft >= 19){
            return BlackJackAction::STAND;
        }
    } else{
        //hard code second
        //Double down first again below:
        if(canDD){
            if(hard == 11 && dealer <= 10){
                return BlackJackAction::DOUBLE_DOWN;
            }
            if(hard == 10 && dealer <= 9){
                return BlackJackAction::DOUBLE_DOWN;
            }
            if(hard == 9 && dealer >= 3 && dealer <=6){
                return BlackJackAction::DOUBLE_DOWN;
            }
        }
        
        if(hard >= 17){
            return BlackJackAction::STAND;
        }
        if(hard <= 11){
            return BlackJackAction::HIT;
        }
        if(hard == 12){
            if(dealer == 4 || dealer == 5 || dealer == 6){
                return BlackJackAction::STAND;
            } else{
                return BlackJackAction::HIT;
            }
        }
        if(hard >= 13 && hard <= 16){
            if(dealer <= 6){
                return BlackJackAction::STAND;
            } else{
                return BlackJackAction::HIT;
            }
        }
    }
    return BlackJackAction::HIT;
}

void BlackJackSolver::take_payout(chip_t chips, std::span<const Card> dealer_cards) {
    totalChips += chips;
}

void BlackJackSolver::on_reshuffle() {
}

