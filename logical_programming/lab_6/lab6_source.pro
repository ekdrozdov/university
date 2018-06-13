domains
	file = textFile; dictFile; newtextFile.
	
	element = string
	list = element*
	dict = list*
	
predicates
	nondeterm replace(string, string, string).
	nondeterm buildDict(string, dict).
	nondeterm replaceText(string, dict, string).
	nondeterm getReplacement(string, dict, string).
	
clauses	
	buildDict("", []).
	
	buildDict(Text, [[ToReplace, Replacement] | Dict]):-
		fronttoken(Text, ToReplace, Rest1),
		fronttoken(Rest1, _, Rest2),
		fronttoken(Rest2, Replacement, Rest3),
		fronttoken(Rest3, _, Rest4),
		buildDict(Rest4, Dict).
	
	getReplacement(Word, [], Word).
	
	getReplacement(Word, [[Word, Replacement] | DictTail], Replacement):-
		!.	
	
	getReplacement(Word, [[_, _] | DictTail], Replacement):-
		getReplacement(Word, DictTail, Replacement).
	
	replaceText("", _, "").
	
	replaceText(Text, Dict, NewText):-
		fronttoken(Text, ToReplace, Rest),
		getReplacement(ToReplace, Dict, Replacement),
		replaceText(Rest, Dict, NewTextBase),
		fronttoken(NewText, Replacement, NewTextBase).
	
	replace(TextFileName, DictFileName, NewTextFileName):-
		openread(dictFile, DictFileName),
		readdevice(dictFile),
		readln(DictText),
		closefile(dictFile),
		buildDict(DictText, Dict),
		
		openread(textFile, TextFileName),
		readdevice(textFile),
		readln(Text),
		closefile(textFile),
		replaceText(Text, Dict, NewText),
		
		openappend(newtextFile, NewTextFileName),
		writedevice(newtextFile),
		write(NewText),
		closefile(newtextFile).
		
goal
	% predicates to hadle strings
	replace("D:\a.txt", "D:\b.txt", "D:\c.txt").
	%buildDict("hi hello, coodda could.", Dict).
	%replaceText("hi,my,name,is,Edward.", [["hi", "hello"]], NewText).