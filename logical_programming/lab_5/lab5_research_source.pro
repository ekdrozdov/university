domains
	function = symbol.
	operation = symbol.

predicates
	nondeterm derivative(string, string, string, string)
	nondeterm derivative(string, string)

clauses
	derivative(X, Result):-
		concat("d", X, Result).
	
	derivative("+", X, Y, Result):-
		derivative(X, DX),
		derivative(Y, DY),
		concat(DX, " + ", Temp_result),
		concat(Temp_result, DY, Result).
	
	derivative("-", X, Y, Result):-
		derivative(X, DX),
		derivative(Y, DY),
		concat(DX, " - ", Temp_result),
		concat(Temp_result, DY, Result).
	
	derivative("*", X, Y, Result):-
		derivative(X, DX),
		derivative(Y, DY),
		concat(DX, " * ", Temp_first_term),
		concat(Temp_first_term, Y, First_term),
		concat(DY, " * ", Temp_second_term),
		concat(Temp_second_term, X, Second_term),
		concat(First_term, " + ", Temp_result),
		concat(Temp_result, Second_term, Result).
	
	derivative("/", X, Y, Result):-
		derivative(X, DX),
		derivative(Y, DY),
		% Numerator
		concat("(", DX, Open_br_num),
		concat(Open_br_num, " * ", Temp_first_term),
		concat(Temp_first_term, Y, First_term),
		concat(DY, " * ", Temp_second_term),
		concat(Temp_second_term, X, Second_term),
		concat(First_term, " - ", Temp_numenator),		
		concat(Temp_numenator, Second_term, Close_br_num),
		concat(Close_br_num, " )", Numerator),
		% Denominator
		concat("( ", Y, Open_br),
		concat(Open_br, " * ", Temp_denominator),
		concat(Temp_denominator, Y, Close_br),
		concat(Close_br, " )", Denominator),
		% Result
		concat(Numerator, " / ", Temp_result),
		concat(Temp_result, Denominator, Result).
		
	
goal
	%some_goal
	derivative("/", "f", "g", X).