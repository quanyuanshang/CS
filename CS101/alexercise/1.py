def max_score(cards):
    n = len(cards)
    dp = [[0] * n for _ in range(n)]
    
    # Initialize the DP table for subarrays of length 1
    for i in range(n):
        dp[i][i] = cards[i]
    
    # Fill the DP table for subarrays of length 2 to n
    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            dp[i][j] = max(
                cards[i] + (sum(cards[i+1:j+1]) - dp[i+1][j]),
                cards[j] + (sum(cards[i:j]) - dp[i][j-1])
            )
    
    return dp[0][n-1]

# Example usage:
cards = [2, 3, 5, 1, 4]
print(max_score(cards))  # Output: Jerry's maximum score