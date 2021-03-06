domains
	element  = integer
	list = element*
	
	%dict_element = el(char); counter(integer)
	dictionary = list*

predicates
	nondeterm print_list(list)
	nondeterm set_list(list, list)
	nondeterm add_to_begin(element, list, list)
	nondeterm add_to_end(element, list, list)
	nondeterm add_to_end_dict(list, dictionary, dictionary)
	
	nondeterm shift_head_to_end(list, list)
	nondeterm shift_last_to_first(list, list)
	nondeterm duplicates(list)
	nondeterm find(list, element)
	nondeterm find_dict(dictionary, element)
	nondeterm insert_after(list, list, list, element)
	nondeterm insert_after__insert(list, list, list, element)
	nondeterm conc(list, list, list)
	nondeterm delete_duplicates(list, list)
	nondeterm delete_duplicates(list, list, element)
	nondeterm compress(list, dictionary)
	nondeterm compress(list, dictionary, list)
	nondeterm contest(list, list)
	nondeterm count_entries(element, list, integer)

clauses
	add_to_end(Element, [], [Element]).
	
	add_to_end(Element, [OldHead | OldTail], [OldHead | NewTail]):-
		add_to_end(Element, OldTail, NewTail).
		
	add_to_end_dict(Element, [], [Element]).
	
	add_to_end_dict(Element, [OldHead | OldTail], [OldHead | NewTail]):-
		add_to_end_dict(Element, OldTail, NewTail).
	
	add_to_begin(Element, List, NewList):-
		NewList = [Element | List].

	shift_head_to_end([Head | Tail], NewList):-
		add_to_end(Head, Tail, NewList).
	
	shift_last_to_first([LastElement | []], [LastElement | []]).
	
	shift_last_to_first([OldHead | OldTail], [NewHead | [OldHead | NewTail]]):-
		shift_last_to_first(OldTail, [NewHead | NewTail]).
	
	print_list(List):-
		List = [Head | Tail],
		write(Head),
		write("\n"),
		print_list(Tail).
		
	set_list(List, Some_list):-
		List = Some_list.
	
	find([Head | Tail], Element):-
		Head = Element;
		find(Tail, Element).
	
	find_dict([[CurrEl, Counter] | Tail], Element):-
		CurrEl = Element;
		find_dict(Tail, Element).
	
	duplicates([Head | Tail]):-
		find(Tail, Head);
		duplicates(Tail).
	
	% author: Schreiner
	conc([], List, List).
	
	% author: Schreiner
	conc([H | T], L, [H | T1]):-
		conc(T, L, T1).

	% Stop recursion when needed element was reached
	% and concatenate appropriately.
	insert_after__insert([Element | BaseTail], InsertList, NewList, Element):-
		conc([Element | InsertList], BaseTail, NewList).
	
	insert_after__insert([BaseHead | BaseTail], InsertList, [BaseHead | NewList], Element):-
		insert_after__insert(BaseTail, InsertList, NewList, Element).
	
	insert_after(BaseList, InsertList, NewList, Element):-
		find(BaseList, Element),
		insert_after__insert(BaseList, InsertList, NewList, Element).
	
	delete_duplicates([Head | Tail], [Head | NewList]):-
		delete_duplicates(Tail, NewList, Head).
	
	delete_duplicates([], [], _).
	
	delete_duplicates([PrevHead | Tail], NewList, PrevHead):-
		!,
		delete_duplicates(Tail, NewList, PrevHead).
	
	delete_duplicates([Head | Tail], [Head | NewList], _):-
		delete_duplicates(Tail, NewList, Head).
	
	count_entries(_,  [], 0).
	
	count_entries(Element, [Element | DTail], CountInc):-
		count_entries(Element, DTail, Count),
		CountInc = Count + 1,
		!.
	
	count_entries(Element, [_ | DTail], Count):-
		count_entries(Element, DTail, Count).
	
	% Note: all duplicates in the List should be placed in a row
	% because of implementation of the "delete_duplicates" predicate
	contest(List, Contest):-
		delete_duplicates(List, Contest).

	compress(List, Dictionary):-
		contest(List, Contest),
		compress(List, Dictionary, Contest).
	
	compress(_, [], []).
	
	compress(List, [[ContestHead, Count] | Dictionary], [ContestHead | ContestTail]):-
		count_entries(ContestHead, List, Count),
		compress(List, Dictionary, ContestTail).	
		
goal
	% standart predicates to handle a lists
	shift_head_to_end([1, 3, 7, 5], NewList).
	%shift_last_to_first([1, 3, 7, 5], NewList).
	%duplicates([1, 3, 7, 5]).
	%conc([4, 5, 6], [1, 2, 3], NewList).
	%insert_after([1, 2, 3], [4, 5, 6], NewList, 2).
	%delete_duplicates([1, 2, 2, 2, 3, 3, 4, 5, 5], NewList).
	%compress([1, 2, 2, 3, 4], NewDict).