domains
	list = string*

predicates
	nondeterm length(list, integer)
	
	nondeterm age(string, integer)
	nondeterm cost_max(string, integer)
	 
	nondeterm languages_dialog
	nondeterm increment(integer, integer)
	nondeterm add_lang(string, string, string)
	nondeterm count(string)
	
	nondeterm clothes_dialog
	nondeterm clothes_dialog_usage
	
	nondeterm selector(string)
	
	nondeterm add_type
	nondeterm add_item
	nondeterm add_cost
	nondeterm add_age_bounds
	
	nondeterm remove_type
	nondeterm remove_item
	nondeterm remove_cost
	nondeterm remove_age_bounds
	
	nondeterm print_current_database_content
	nondeterm exit_program
	
	%nondeterm print_content
	%nondeterm exit_program
	
database - languages_dbase
	lang(string)
	speak(string, string)
	
database - clothes_dbase	
	clothes_type(string)
	in_stock(string, string)
	age_bounds(string, integer, integer)
	cost(string, integer)
	
clauses
	% --- Task #1 --- %

	length([], 0).
		
	length([Head | Tail], Count):-
		length(Tail, NewCount),
		Count = NewCount + 1.
	
	cost_max(X, Y):-
		cost(X, A),
		A <= Y.
	
	age(X, Y):-
		age_bounds(X, A, B),
		Y >= A,
		Y <= B.
	
	increment(X, IncX):-
		IncX = X + 1.
	
	add_lang("yes", User_name, Suggested_language):-
		assertz(speak(User_name, Suggested_language), languages_dbase).
	
	languages_dialog:-
		write("Enter your name: "),
		readln(User_name),
		lang(Suggested_language),
		write("Do you speak "),
		write(Suggested_language, "\n"),
		readln(Respond),
		add_lang(Respond, User_name, Suggested_language),
		fail.
	
	count(User_name):-
		consult("D:\languages.dba", languages_dbase),
		findall(L, speak("ed", L), List),
		length(List, Count),
		write(Count, "\n").
		
	% --- Task #2 --- %
	
	add_type:-
		write("Enter type name to add\n"),
		readln(Type_name),
		assertz(clothes_type(Type_name), clothes_dbase).
		
	add_item:-
		write("Enter (item_name, item_type) to add\n"),
		readln(Item_name),
		readln(Type_name),
		assertz(in_stock(Item_name, Type_name), clothes_dbase).
		
	add_cost:-
		write("Enter (item_name, cost) to add\n"),
		readln(Item_name),
		readint(Cost),
		assertz(cost(Item_name, Cost), clothes_dbase).
		
	add_age_bounds:-
		write("Enter (item_name, bottom_bound, top_bound) to add\n"),
		readln(Item_name),
		readint(Bottom_bound),
		readint(Top_bound),
		assertz(age_bounds(Item_name, Bottom_bound, Top_bound), clothes_dbase).
		
	remove_type:-
		write("Enter type name to remove\n"),
		readln(Type_name),
		retract(clothes_type(Type_name), clothes_dbase).
		
	remove_item:-
		write("Enter (item_name, item_type) to remove\n"),
		readln(Item_name),
		readln(Type_name),
		retract(in_stock(Item_name, Type_name), clothes_dbase).
		
	remove_cost:-
		write("Enter (item_name, cost) to remove\n"),
		readln(Item_name),
		readint(Cost),
		retract(cost(Item_name, Cost), clothes_dbase).
		
	remove_age_bounds:-
		write("Enter (item_name, bottom_bound, top_bound) to remove\n"),
		readln(Item_name),
		readint(Bottom_bound),
		readint(Top_bound),
		retract(age_bounds(Item_name, Bottom_bound, Top_bound), clothes_dbase).
		
	exit_program:-
		fail.
		
	print_current_database_content:-
		write("Type | name | ages | cost |\n"),
		in_stock(Item_name, Item_type),
		age_bounds(Item_name, Bottom_bound, Top_bound),
		cost(Item_name, Item_cost),
		write(Item_type),
		write("   "),
		write(Item_name),
		write("   "),
		write(Bottom_bound),
		write(" - "),
		write(Top_bound),
		write("   "),
		write(Item_cost),
		write("\n").
			
	clothes_dialog_usage:-
		write("--- Main menu ---\n"),
		write("1 -- add a type\n"),
		write("2 -- add an item\n"),
		write("3 -- add a cost\n"),
		write("4 -- add an age bounds\n"),	
		write("\n"),	
		write("-1 -- remove a type\n"),
		write("-2 -- remove an item\n"),
		write("-3 -- remove a cost\n"),
		write("-4 -- remove an age bounds\n"),
		write("\n"),
		write("9 -- print content of current database\n"),
		write("10 -- load database\n"),
		write("11 -- save database\n"),
		write("0 -- exit\n").
		
	selector("1"):-
		add_type.
		
	selector("2"):-
		add_item.
		
	selector("3"):-
		add_cost.
		
	selector("4"):-
		add_age_bounds.
		
	selector("-1"):-
		remove_type.
		
	selector("-2"):-
		remove_item.
		
	selector("-3"):-
		remove_cost.
		
	selector("-4"):-
		remove_age_bounds.

	selector("9"):-
		print_current_database_content.
		
	selector("10"):-
		consult("D:\clothes.dba", clothes_dbase).
		
	selector("11"):-
		save("D:\clothes.dba", clothes_dbase).
		
	selector("0"):-
		exit_program.
	
	clothes_dialog:-
		clothes_dialog_usage,
		readln(Respond),
		selector(Respond),
		clothes_dialog.
		
	lang("English").
	lang("German").
	lang("Italian").
	lang("Franch").
	lang("Japanese").
		
goal
	% count number of speaked langu-s
	%languages_dialog; save("D:\languages.dba", languages_dbase).
	count("ed").
	%consult("D:\languages.dba", languages_dbase), findall(L, speak("ed", L), List).
	%clothes_dialog.