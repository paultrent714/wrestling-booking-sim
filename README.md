# Toaster Wrestling

Toaster Wrestling is a working title, which is based off my username in online games.
The goal is to create a text heavy pro wrestling roster management simulation game similar to franchise modes in sports video games. The player gets to build and manage a roster, create storylines, try to gain fans through high match ratings, and handle finances. This drew heavy inspiration from indie games such as MDickie games, ZenGM's sports management games, and Pocket GM games by Jonathan Howell. 

Gameplay involves booking and deciding the winners of different types of matches, building teams and rivalries, handling championships, signing new wrestlers, managing a roster's health, and watching individual wrestlers improve over time.

This game is intended to be the foundation of more complex management games of other sports such as football.

Each wrestler 12 main attributes. They include age, role (hero, neutral, or villain), popularity value (affects odds to win a match when player chooses "random winner"), charisma, health (low health increases likelihood and severity of injury), stamina (affects how quickly health decreases from a match). There are 5 main attributes related to in-ring styles that affect the quality of the matches: Powerhouse, Brawler, High Flyer, Technician, and MMA. The final attribute is a potential rating which is shown only to the player as an A to F letter grade. Potential is the maximum value the in ring style attributes can all sum up to.

Each wrestler in a player's roster will have a contract for a set number of matches with a salary based entirely on the wrestler's popularity at the time of signing. As a wrestler's popularity changes, the player can choose to sign an extension that will give the wrestler a different salary when the current contract expires.

This was created mainly in C++ and Qt. SQLite is used for saving/loading player's game data as well as loading the default roster. 


## Features

### Mostly Complete Features

- Randomly generated wrestlers can be used in game setup
- Match booking UI with single, team, and title matches
- SQLite save/load system
- Title holders can be manually be edited
- Roster list shows each wrestler's name along with relevant stats
- Roster can be sorted by common attributes
- Wrestler attribute growth with diminishing returns
- Health/injury system allows for no wrestler to be mathematically guaranteed  to be injured or healthy after a match
- Includes graphs which show fan and money growth over time
- Free Agency


### Partial Features (Working, but needs improvement)
- A lot of game balancing in the formulas for wrestler improvement, match rating, fan change, finance, etc 
- User can select a "Random Winner" 
    - Currently uses weighted probability based on the popularity of the participants
    - Planned: include effects of champions and of teams in the match 
- "Scout Talent" 
    - Choose to sign new randomly generated wrestler to promotion as a rookie
    - Rookie attributes not yet properly balanced
- Salary Display
    - Player can only see current salary of a wrestler, 
    - Planned: will also show the salary of an already signed extension and when the extension's salary starts
- Teams
    - Team name and participants can be edited
    - There is not yet any affect to match rating or "random winner" odds to a team being in a match 
- Feuds 
    - Can only be created by user
    - Feud length and cooldown length need to be balanced
    - Not yet any affect to match rating
- Wrestlers go to Free Agency when their contracts with their employer expire
    - Planned: Free agent wrestlers stats can change over time
- CPU Promotions
    - CPU promotion will evaluate signings to keep a minimum roster size
    - CPU will compete with player's promotion and gain fans and money
    - Planned: championships, teams, match card for CPU
    - Planned: CPU wrestlers stats can change over time
- Random Name Generation 
    - Over 250,000 possible combinations of randomly generated names currently each have equal probabilities of occurring, 
    - Planned: more common names will at some point be adjusted to have higher probabilities (low priority)
- Wrestler Faces
    - Currently selects a random PNG from a set of default faces, which were created with a [modified version](https://github.com/paultrent714/facesjs.git) of [facesjs](https://zengm.com/facesjs/ ), ZenGM's opensource JavaScript face generator
    - Planned: player can use the modified version to create their own faces and save them as the wrestler's face, or use existing images as face


### Planned Features (Yet to be implemented)
- Interviews and other aspects of the show that use Charisma
- More match types 
- Multiple teams in a match
- More options for types of championships that can be used
- Ability to create and load custom rosters
- Pay Per Views instead of only having Weekly Shows
- Morale system that affects wrestlers' asking price when being signed/resigned


This project is designed to be modular and expandable. While it currently focuses on pro wrestling, the underlying systems (match simulation, stat progression, database management) are being built with multi-sport management in mind.

Currently, this game only works in Qt Creator.

healing_red.png and healing_white.png came from Google Material Symbols
settings and arrow .png files all came from https://iconmonstr.com
championship png was made with pixlr.com




https://fonts.google.com/attribution
https://iconmonstr.com/license/

