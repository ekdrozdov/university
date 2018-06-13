domains
	term = integer.
	exp = conj(exp, exp); disj(exp, exp); neg(exp); term
	
predicates
	nondeterm tautology(exp).
	
clauses	
	tautology(disj(A, neg(A))).
	
	tautology(neg(A)):-
		not(tautology(A)).
	
	tautology(conj(A, B)):-
		tautology(A),
		tautology(B).
	
	tautology(disj(A, B)):-
		tautology(A);
		tautology(B).
goal
	%tautology(disj(term, neg(term))).
	tautology(disj(term, term)).
	%tautology(conj(disj(term, neg(term)), term)).
	%tautology(conj(disj(term, neg(term)), disj(term, neg(term)))).