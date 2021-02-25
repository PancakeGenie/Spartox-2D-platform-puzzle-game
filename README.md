# Spartox

Developed with Unreal Engine 4. Game is being developing mainly with C++. Blueprints nodes are used, but not as much. 
It's my first game and I am using it to learn how to program UE4 games with C++ and BP's. It might have a lot of mistakes.
If someone stumbles upon this masterpiece, have fun with all the bu... "features" it has!

Game is a simple puzzle platformer where you switch control between 2 controllable players and need to collect the key before reaching the end platform.
It's played on 2D plane but designed in 3D space. Really nothing much more to say. Just a couple of boxes you control by moving, jumping, destroying objects and picking up a key to reach the end level. Very creative, much wow.

The only thing it has is a tutorial, which is still incomplete. Never did level design, nor did I use trigger boxes, so I am working on creating the tutorial level before continuing to work on players/interactable objects.

Anyway, any criticism is welcomed, I wish to improve so don't go easy on me by pulling the punches! I have a really thick skin, so go right ahead.

To do now:
1) Create a tutorial level!
2) Add special ability for each of the two players (red and blue)
3) Two more small levels
4) Few more needed models (key, end level platform, begin level platform, etc.)

Things to fix soon:
1) Jump (resets on horizontal collision with objects, needs to reset only if it hits the floor. So... needs to check Z impact point only)
2) Player bounce of wall (pretty sure why this is happening, but not sure enough. Think it's because I am using "AddWorldOffset" function....needs more testing)
3) Interactable object not sliding on level (basically floor collision is preventing the pushed object to slide because the pushed object hits the edge of the floor collision box)
4) Camera stutter on collision (this might be related to 2. point, because "AddWorldOffset" wants to move, so camera moves but player stays on same spot so camera needs to move back...which causes the stutter to happen. Needs more testing)

In future:
1) Add particle effects
2) Add some animations
3) Add sound
4) Create a background (maybe even ANIMATED background!!!! This fog is making me nauseated)
