predicates
	nondeterm shorts(symbol)
	nondeterm shirt(symbol)
	nondeterm pants(symbol)
	nondeterm hat(symbol)
	
	nondeterm age_bounds(symbol, integer, integer)	
	nondeterm age(symbol, integer)
	
	nondeterm cost(symbol, integer)
	nondeterm cost_max(symbol, integer)
	
clauses
	cost_max(X, Y):-
		cost(X, A),
		A <= Y.
	
	age(X, Y):-
		age_bounds(X, A, B),
		Y >= A,
		Y <= B.
	
	shorts(shorts_a).
	shorts(shorts_b).
	shorts(shorts_c).
		
	shirt(shirt_a).
	shirt(shirt_b).
	shirt(shirt_c).
	
	pants(pants_a).
	pants(pants_b).
	pants(pants_c).
	
	hat(hat_a).
	hat(hat_b).
	hat(hat_c).
	
	age_bounds(shorts_a, 3, 10).
	age_bounds(shorts_b, 2, 3).
	age_bounds(shorts_c, 5, 8).
	
	age_bounds(shirt_a, 3, 5).
	age_bounds(shirt_b, 5, 8).
	age_bounds(shirt_c, 8, 10).
	
	age_bounds(pants_a, 4, 7).
	age_bounds(pants_b, 3, 10).
	age_bounds(pants_c, 3, 10).
	
	age_bounds(hat_a, 8, 10).
	age_bounds(hat_b, 5, 5).
	age_bounds(hat_c, 1, 2).
	
	cost(shorts_a, 100).
	cost(shorts_b, 200).
	cost(shorts_c, 300).
	
	cost(shirt_a, 110).
	cost(shirt_b, 500).
	cost(shirt_c, 250).
	
	cost(pants_a, 300).
	cost(pants_b, 170).
	cost(pants_c, 580).
	
	cost(hat_a, 30).
	cost(hat_b, 20).
	cost(hat_c, 50).
	
goal
	%age(X, 5), cost_max(X, 400).
	%age(X, 4), age(X, 10).
	%shirt(X), cost(X, Y).
	%age(X, 3), not(shirt(X)), hat(Y),  cost(X, A), cost(Y, B), A + B <= 600.
	cost_max(X, 100).