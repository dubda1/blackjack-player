#include "black_jack_solver.hpp"

BlackJackSolver::BlackJackSolver(
    uint64_t number_of_decks,
    float reshuffle_percentage,
    uint64_t number_of_rounds,
    chip_t chips,
    chip_t table_min,
    chip_t table_max)
{
}

int handValue(std::span<const Card> cards);

BlackJackSolver::~BlackJackSolver() {}

chip_t BlackJackSolver::get_bet() { return 0; }

BlackJackAction
    BlackJackSolver::handle_hand(Card dealer_up_card, std::span<const Card> cards, BlackJackHandStatus status)
{
    int value = handValue(cards);
    if(dealer_up_card.rank >= 9 && cards){

    }
    std::cout << value <<endl;
    return BlackJackAction::STAND;
}

void BlackJackSolver::take_payout(chip_t chips, std::span<const Card> dealer_cards) {}

void BlackJackSolver::on_reshuffle() {}

int handValue(std::span<const Card> cards){
    int value = 0;
    for (int i = 0; i < cards.size(); i++) {
        value += static_cast<int>(cards[i].rank);
    }
    return value;
}