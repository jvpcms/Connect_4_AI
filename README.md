# Connect 4 AI using the Minimax algorithm

### Minimax algorithm:

- In a turn-based game, the Minimax algorithm can be used to determine the best play at each move.
- One player is the maximizing player, and the other is the minimizing player.

### How it works:

- The algorithm works recursively; when trying to decide the best move in a given state, it will try all possible moves, and for each one, it will call the recursive function in order to determine the best move of the next player (it assumes the opponent will always pick the best move).
- The current player is passed as a parameter to the function; if it is the maximizing player's turn, the function will find the move with the maximum evaluation score and return it, propagating the score to the previous call.
- If it is the minimizing player's turn, the function will find the move with the minimum evaluation score and return it.
- The move picked is the one that returns the highest value in the original call.

### Alpha-beta pruning:

- The alpha and beta parameters are used to keep track of the highest and lowest scores found so far in that particular instance of the function.
- In the maximising players turn, if the best possible score we can find is already lower than the score found in a previous branch, we can stop searching in the current branch.
- In the minimizing player turn, if the best possible score we can find is already higher than the score found in a previous branch, we can stop searching in the current branch.
- In the situation where the best branch is among the last branches checked, the algorithm will not have an advantage. So it is best to check the
most promising branches first. In this case, it's generally better to check the middle columns first.

### Limit depth:

- The algorithm can be very slow if the depth is too high, so we can set a maximum depth and break the recursion when it reaches it.
