/*

Level end on ball loss
V 1. Platform melt animation
V 2. Animation of rolling out a new
V 3. Animation of the expanding platform
V 4. Launching the ball with a space and the state of the ball

bricks
V 1. Ordinary bricks (blue or red)
V 1.1. Can be with or without letter
V 1.2. When hitting a brick, it disappears from the level immediately, and if the brick was:
v 1.2.1. Without a letter - an active brick is created
v 1.2.2. With a letter - a falling letter is created

2. Indestructible brick
2.1. On-hit animation

3. Reusable brick
3.1. 4 brick states (1-4 hits before breaking)
3.2. State Transition
3.3. Prize animation when destroyed (brick disappears, animation remains)

4. Brick with a parachute
4.1. Parachute animation - as a variant of the falling letter

5. Brick of teleportation
5.1. Animation when capturing and releasing the ball

6. Advertising brick
6.1. Animation of a fragment of "advertising" hidden behind a brick


Interaction of special bricks
V 1. Falling letter - only interacts with the platform
2. Active brick - interacts only with the ball


Actions of letters
1. Simple:
1.1. O ("Cancel") - cancels the action of the symbols K, W, P, L and M.
1.2. I ("Invert")
1.3. S ("Speed")
1.4. M ("Monsters")
1.5. F ("Life")


2. Complex:
2.1. K ("Glue")
2.1.1. New state of the platform
2.1.2. Spreading glue animation (forward and reverse)
2.1.3. Fixing the ball (+ new state of the ball)
2.1.4. Ball launch by space and timeout

2.2. W ("Wider")
2.2.1. New platform state (+ resizing)
2.2.2. Expanding platform animation (forward and reverse)

2.3. P ("Floor")
2.3.1. Floor rendering
2.3.2. floor scale
2.3.3. The interaction of the floor with the ball
2.3.4. Hitting the ball with the bottom edge of the platform

2.4. L ("Laser")
2.4.1. New state of the platform
2.4.2. Animation of transforming into a cannon (forward and reverse)
2.4.3. Space Shooting:
2.4.3.1. Gap handling in a special way when the platform is in laser mode
2.4.3.2. Laser beam objects - animation, movement and interaction with other objects

2.5. T ("Three")
2.5.1. Add support for multiple balls
2.5.2. Output of many balls
2.5.3. Interaction of many balls with game elements

2.6. + (Go to the next level)
2.6.1. Animation of early transition to the next level
2.6.2. Separate transition level with special walls (frame)

ball movement
V 1. Bounce of the ball from the frame
V 2. Hitting the edges of the platform
V 3. Sweeping the ball with a platform
4. Hitting the monster

Hitting a brick
1. Hitting a brick - the state of a brick
V 2. Knocking out a falling letter
V 3. Interception of a falling letter
4. Each letter has its own actions

Gates
1. Output gates
2. Animation of opening/closing gates
3. Gate states (closed, opening, closing)


Monsters
1. List of monsters (eye, "turtle", "saturn", head, "tambourine", aquarium, lighter)
2. For everyone - make a storyboard
3. Move, select direction + states (live/pause/disappear)
4. Interaction with the ball and the platform
5. Exit the gate
6. For everyone - animation


Information panel
1. Logo
2. Indicators
2.1. Player name
2.2 Checking account
3. Scale of monsters and gender
4. Change scales
5. Extra lives window
6. Accounting for game actions and display on indicators


Game and levels
1. List of the first 10 levels
2. Game states (splash screen, animation of the beginning of the level, playing the level, loss of life, transition to the next level (normal and early), end of the game)


*/