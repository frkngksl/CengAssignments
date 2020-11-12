:- module(hw5, [catomic_number/2, ion/2, molecule/2]).
:- [catoms].
catomic_number(NAME,CATOMIC_NUMBER):-catom(NAME, _ , _, ELECTRON_LIST),
                                     electron_number(ELECTRON_LIST,CATOMIC_NUMBER).

electron_number([],0).
electron_number([H|T],N):-
                          electron_number(T,M),
                          N is M+H.
ion(NAME,CHARGE):-catom(NAME,_,_,ELECTRON_LIST),
                   outerShell(ELECTRON_LIST,M),
                   (M=<4 -> CHARGE is M;CHARGE is M-8).

outerShell([Head],Head):-!.
outerShell([_|T],N):-outerShell(T,N).

ionNums([],0).
ionNums([H|T],N):-ionNums(T,M),
                  ion(H,X),
                  N is X+M.

isAscendingOrder([]).
isAscendingOrder([_]).
isAscendingOrder([X,Y|T]) :-
    catomic_number(X,Xnum),
    catomic_number(Y,Ynum),
    Xnum=<Ynum,
    isAscendingOrder([Y|T]).



adder([Head],X,Z):- catomic_number(Head,X),
                         ion(Head,Z).

adder([H,FURU|T],TOTAL_CATOMIC_NUMBER,Z):-
                                      catomic_number(H,X),
                                      TOTAL_CATOMIC_NUMBER >= X,
                                      M is TOTAL_CATOMIC_NUMBER-X,
                                      catomic_number(FURU,NURU),
                                      X =< NURU,
                                      ion(H,MAMET),
                                      YETER is Z-MAMET,
                                      adder([FURU|T],M,YETER).


molecule(CATOM_LIST,TOTAL_CATOMIC_NUMBER):- adder(CATOM_LIST,TOTAL_CATOMIC_NUMBER,0).
