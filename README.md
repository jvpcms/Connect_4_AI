# Connect 4 AI using Minimax algorithm

### Minimax algorithm:

In a turn based game the minimax algorithm can be use to determine the best play at each move.
One player is the maximazing player and the other is the minimizing player.

### How it works:

- The algorithm works recursively, when tryin to decide the best move in a given state, it will try all possible moves and, for each one, it will call the recursive function
to determine the best move of the next player (it asumes the opponent will allways pick the best move).
- The current player is passed as a parameter to the function, if it is the maximazing player's turn, the function will find the move with maximum evaluation score
and return it, propagating the score to the previous call.
- If it is the minimizing player's turn, the function will find the move with minimum evaluation score and return it.
- The move picked is the one that returns the highest value in the original call.

### Alpha-beta pruning:

- The alpha and beta parameters are used to keep track of the highest and lowes scores found so far in that particular instance of the function.
- In the maximazing players turn, if the best possible score ww can find is already lower than the score found in a previous branch, 
we can stop searching in the current branch.
- In the minimizing players turn, if the best possible score we can find is already higher than the score found in a previous branch,
we can stop searching in the current branch.
- In the situation that the best branch is among the last branches checked, the algorithm will not have an advantege. So it is best to check the
most promising branches first. In this case, its generally better to check the middle columns first.

### Limit depth:

- The algorithm can be very slow if the depth is too high, so iwe can set a maximum depth and break the recursion when it reaches it.
