# Getting Started

Follow these steps to set up your own copy of this repository and personalize
it.

## 1. Fork this repository

1. In your browser, go to the GitHub page for this repo.
2. Click the **Fork** button (top-right).
3. Make sure the fork is created under **your** GitHub account.

## 2. Clone *your* fork

On your own machine, clone the fork you just created:

```bash
git clone https://github.com/<your-github-username>/blackjack-player.git
cd blackjack-player
```

Replace `<your-github-username>` with your actual GitHub username.

## 3. Rename the `player` directory with *your* name

You must rename the existing `player` directory to a directory with your own
name using `git mv player <your-name>`, so Git tracks the rename properly.

For example, if your name is Walter Goodzey, you would use:

```bash
git mv player walter-goodzey
```

Doing first name and last initial or github username is also fine (e.g., `walter-g`, `wimos-ai`).

### Guidelines

- Use all **lowercase**
- use **hyphens** instead of spaces (e.g., `walter-goodzey`)
- Do **not** delete and recreate the directory, use `git mv` to have a clean
version history

## Commit your change

```bash
git status    # Check that you made changes registered by git
git add .
git commit -m "Renamed player directory to my name"
```

## Push your changes to your fork

```bash
git push origin main
```

## Build your code

```bash
./blackjack.sh build
```

# Evaluating your Algorithm

## Build your code

```bash
./blackjack.sh build
```


## Run Code
```bash
./blackjack.sh test
```
This will find your compiled `.so` produced by the build system, and run it using `./bin/blackjack_runner.out`.
Documentation for the executable can be found by running `./bin/blackjack_runner.out` in your terminal.

## Inspect `out.json`
Running your code will generate a logfile, `out.json` by default. This file will contain the evaluation metrics for your algorithm.

### Full Example
```json
{
	"number_of_decks": 2,
	"reshuffle_percentage": 0.5,
	"number_of_rounds": 5,
	"chips": 500,
	"table_min": 5,
	"table_max": 50,
	"rounds": [
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [],
				"split_hand": null
			},
			"result": "BUYIN"
		},
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [
					"9C",
					"JS"
				],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [
					"6D",
					"AS"
				],
				"split_hand": null
			},
			"result": "OK"
		},
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [
					"TH",
					"KD"
				],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [
					"8D",
					"TS"
				],
				"split_hand": null
			},
			"result": "OK"
		},
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [
					"TD",
					"TS"
				],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [
					"JS",
					"AH"
				],
				"split_hand": null
			},
			"result": "OK"
		},
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [
					"2S",
					"6D"
				],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [
					"TC",
					"QC"
				],
				"split_hand": null
			},
			"result": "OK"
		},
		{
			"dealer": {
				"owned_chips": 0,
				"bet": 0,
				"hand": [
					"9H",
					"KD"
				],
				"split_hand": null
			},
			"player": {
				"owned_chips": 500,
				"bet": 0,
				"hand": [
					"AS",
					"5H"
				],
				"split_hand": null
			},
			"result": "OK"
		}
	],
	"valid_rounds": 6,
	"invalid_rounds": 0,
	"mean_dealer_bet": 0,
	"mean_dealer_chip_per_round": 0,
	"mean_player_bet": 0,
	"mean_player_chip_per_round": 0
}
```

### Explanation of the configuration log

The first couple parameters log the game configuration:
```json
"number_of_decks": 2,
"reshuffle_percentage": 0.5,
"number_of_rounds": 5,
"chips": 500,
"table_min": 5,
"table_max": 50,
```

### Explanation of the round logging
Rounds is an array which contains a log of each hand played. The log is created at the end of the hand.
An example hand is here:
```json
{
"dealer": {
    "owned_chips": 0,
    "bet": 0,
    "hand": [
        "2S",
        "6D"
    ],
    "split_hand": null
},
"player": {
    "owned_chips": 500,
    "bet": 0,
    "hand": [
        "TC",
        "QC"
    ],
    "split_hand": null
},
"result": "OK"
}
```
* `owned_chips` is the number of chips owned by either the dealer or player at the end of the round.
* `bet` is the quantity of chips bet in the round
* `hand` is the cards as they were at the end of the hand. Each card is represented by two ascii charecters. 
    * The first is the rank (A,K,Q,J,T,9,8,7,6,5,4,3,2). 
    * The second is the suit H(earts), D(iamonds), C(lubs), S(pades). 
* `split_hand` is null if the actor did not split, or the hand at the end of the deal
* `result` is an error code. 
    * Possible Error Codes : 
        ```cpp
        enum class RoundResult
        {
            OK,
            BUYIN,
            SURRENDERED,

            INVALID_SPLIT,
            INVALID_SURRENDER,
            INVALID_HIT_BUSTED_TALLY,
            INVALID_DD_AFTER_DRAW,
            INVALID_DD_AFTER_DD,
            INVALID_BET,
            INVALID_ACTION,

            INTERNAL_CATASTROPHE,
        };
        ```
    * `Surrendered`,`OK`, and `BUYIN` indicate successful rounds. 
    * `INTERNAL_CATASTROPHE` means there is an error with the runner code. 
    * The rest mean that the player has taken an illegal action. Eg. `INVALID_DD_AFTER_DD` means that the player tried to double down after doubling down.

### Explanation of final metrics
```json
"valid_rounds": 6,
"invalid_rounds": 0,
"mean_dealer_bet": 0,
"mean_dealer_chip_per_round": 0,
"mean_player_bet": 0,
"mean_player_chip_per_round": 0
```
* `valid_rounds` is how many rounds the player played according to the rules.
* `invalid_rounds` is how many rounds the player broke the rules.
* `mean_dealer_bet` is the average dealer bet across all rounds
* `mean_dealer_chip_per_round` is the average dealer profit across all rounds. Positive is profit, negative is loss.
* `mean_player_bet` is the average player bet across all rounds
* `mean_player_chip_per_round` is the average player profit across all rounds. Positive is profit, negative is loss.

# Scoring
All player AI's will be ran against the same dealer under the same parameters. Each run will produce a `JSON` log file that acts as their score card. 
1. The players will be ranked first according to `valid_rounds`
2. In event of a tie for the first criterion, the players will be ranked according to `mean_player_chip_per_round`
3. In event of a tie on the second criterion, the players will be ranked in reverse order of `mean_player_bet`

## Example Scores

### Player 1
```json
...
"valid_rounds": 10,
"invalid_rounds": 1,
...
"mean_player_bet": 1,
"mean_player_chip_per_round": 1000
```
### Player 2
```json
...
"valid_rounds": 11,
"invalid_rounds": 0,
...
"mean_player_bet": 1,
"mean_player_chip_per_round": 5
```

### Player 3
```json
...
"valid_rounds": 11,
"invalid_rounds": 0,
...
"mean_player_bet": 0.5,
"mean_player_chip_per_round": 5
```

## Example Ranking and Explanation
The ranking of the three players is as follows:
1. Player 3
2. Player 2
3. Player 1

Player 1 scored the lowest in the `valid_rounds` category and goes last. Players 2 and 3 tied on the `mean_player_chip_per_round` parameter, so were ranked by `mean_player_bet`. Player 3 hand a lower mean player bet, so they won.

# Runner Documentation
```bash
Usage: ./bin/blackjack_runner.out [OPTIONS]

Blackjack simulation engine.

Required options:
  -d, --dealer     <file.so>   Dealer plugin shared library
  -p, --player     <file.so>   Player AI shared library
  -o, --output     <file.json> Output dump file
  -n, --ndecks     <int>       Number of decks (> 0)
  -r, --reshuffle  <float>     Reshuffle percentage. How much of the deck is remaining when a reshuffle happens. [0,1]
  -R, --rounds     <int>       Number of rounds (> 0)
  -s, --starting   <int>       Starting chips (> 0)
  -m, --min        <int>       Table minimum (>= 0)
  -M, --max        <int>       Table maximum (> 0, >= min)

Other options:
  -h, --help                   Show this help message
      --version                Print version information
```

# Rules
[General Rules](https://www.blackjackapprenticeship.com/how-to-play-blackjack/)

Extra Rules: 
1. Must run under [Valgrind](https://en.wikipedia.org/wiki/Valgrind) without errors
2. Dealer doesn't hit soft 17
3. Split only once
4. Can double down after splitting
5. Can double down and split even if you don't have sufficient funds. Loss will send you negative and end the game.
6. Stand if given a busted hand
7. Can't surrender after first action on a hand or after splitting
8. Illegal actions lead to automatic draws and the round being counted as invalid.
