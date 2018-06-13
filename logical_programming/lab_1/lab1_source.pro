predicates
	nondeterm parent(symbol, symbol)
	nondeterm lucky(symbol)
	nondeterm gender(symbol, symbol)
	nondeterm twochildren(symbol)
	nondeterm sis_bro(symbol)
	nondeterm grandson(symbol, symbol)
	nondeterm sister(symbol, symbol)
	nondeterm aunt(symbol, symbol)
	nondeterm predecessor(symbol, symbol)

clauses
	parent(pam, bob).
	parent(tom, bob).
	parent(tom, liz).
	parent(bob, ann).
	parent(bob, pat).
	parent(pam, jim).
	
	lucky(Name):-
	parent(Name,_).
	
	gender(pam, female).
	gender(tom, male).
	gender(bob, male).
	gender(liz, female).
	gender(ann, female).
	gender(jim, male).
	gender(pat, male).
	
	sis_bro(Name):-
	parent(X,Name) and  parent(X,Name2) and Name><Name2.
	twochildren(Name):-
	parent(Name,X) and sis_bro(X).
	
	grandson(F,S):-
	parent(F, X) and parent(X, S) and gender(S, male).
	
	sister(Name,Name2):-
	parent(X,Name) and parent(X,Name2) and Name><Name2 and gender(Name,female).
	
	aunt(Name,Name2):-
	parent(X,Name2) and sister(Name,X).
	
	predecessor(X, Z) :-
	parent(X, Z).
	
	predecessor(X, Z) :-
		parent(X, Y),
		predecessor(Y, Z).
goal
	%parent(jim,X).
	%parent(X,jim).
	%parent(pam,X),parent(X,pat).
	%parent(pam,X),parent(X,Y),parent(Y,jim).
	%parent(Who,pat).
	%parent(liz,Who).
	%parent(Who,pat),parent(X,Who).
	
	%lucky(pam).
	
	%twochildren(pam).
	%grandson(Name,Name1).
	%aunt(Name,Name2).
	predecessor(Who, ann).