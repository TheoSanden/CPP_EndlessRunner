Endless Runner C++ 

This is a project for a C++ course I took at futuregames. The goal was to create an Endless runner with effective use of c++, using appropriate storing methods, optimized code, and appropriate memory handling.
Since I did not manage to create README for the first part i hope that an overarching document works for both hand-ins.

----------------------------------------
Table of Contents:

1. Scrolling environment:

 -Obstacle Spawner
	-Moving ObstacleSpawner
2.Character:

 -LocalMultiplayerInputManager 
 	-Movable Character

3.Point system:

 -Score Tracker

4.Game mode
	
----------------------------------------


Scrolling environment:

I decided to go for a stationary solution for the scrolling environment. Although It's unlikely that the character would travel out of range of Unreal 5's coordinate boundaries I decided that it would be coneptually easier to have the character stationary and the environment moving. 

Obstacle Spawner:
The obstacle spawner handles Instantiation and handling of all moving and environmental objects. In order to save on memory and CPU usage I created a template Actor pooler that handles hiding and showing as well as storing actors when not in use. Every frame, the obstacle spawner checks the first index of active actors to see if they've moved off screen and puts them back into the pool. The platforms that the character runs on is handled by this script since it doesn't need more functionality than that. Spawning and placing platforms are done mathimatically and are frame independant so that if a frame drops the platforms will be moved appropriately so that there won't be gaps. I decided to use math since I figured that this would be less preformance heavy incase we would like to spawn a high number of objects.

Moving Obstacle spawner:
The moving obstacle spawner inherits from the obstacle spawner but extends functionality to allow me to spawn different kinds of objects and displace them across the moving platforms. This script uses a weighted list of obstacles to allow for variety in obstacles we want to spawn. Just like the obstacle spawner, this script uses a pool to save on memory. The pools are stored in a Map and are created dynamically based on the objects we put in the spawn array. The weights can be recalculated dynamically in case we wanted to alter the spawn weights during runtime, although this is not implemented.




Character:

The characters where the hardest part of this project to wrap my head around. I decided early that I wanted to do local multiplayer using only the keyboard. But it proved harder than I expected. I went through multiple iterations trying to bind two characters to one controller. After a while I found out that Unreal engine only supports binding one controller to one character. So I scrapped the code I had and decided to channel all input through a "god" character script that delegated the appropriate input to the correct character. Although, this also seemed to not be working. Soon after that i also found out that Unreal's template characters can NOT be moved without being bound to a controller, even if you supply the correct inputs. The only reason I wanted to have the original template characters was because I thought that the animations were real so instead I decided to create my own character controllers. 

LocalMulitplayerInputManager: 
The LocalMuliplayerInputManager recieves all input from the player controller and then relays that information over to the correct character.

Movable Character:
The Movable Character script allows a pawn to move from side to side and jump. It also handles "turning off" a character when it dies.


Point system:

A character will gain points when jumping over an obstacle and passively when progressing through the level. You will also lose points when dying. When you jump over an obstacle the character will collider with an invisible collider; that object will send the character's Unique ID to the game mode and the game mode will communicate with the score tracker which character should get the points. I had a problem where the collision system would register muliple overlaps event withing the same frame and thus giving the character to many points. To solve this, I added a Hashset that records which players it has interacted with, which I then clear when the character exits the collider. I have to clear it like this because I reuse all obstacles and if I didn't the next time the character would jump over the same obstacle they wouldn't recieve the points.

Score Tracker:

The Score Tracker handles keeping score and updating the UI. It also handles saving the Highscore to the save file as well as displaying it.

Game Mode: 
Almost everything is handled through the game mode such as respawning the character, deciding when the game is over, adding score, and potentially destroying obstacles (Although I have not had the time to implement this). The only thing that the game mode handles directly is spawning and respawning players. Everything else is handled through the other scripts I've mentioned. The reason I put most script references in the game mode is because I did not want every object to have to have a reference to their manager scripts. For example, when you jump over an obstacle you gain points. The obstacle itself keeps track of this and sends its information to the game mode. The game mode is accessible from all actor scripts and so this bypasses the need to initialize all objects with a reference to the score tracker.

