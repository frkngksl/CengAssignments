module Hw2 where

data ASTResult = ASTError String | ASTJust (String, String, Int) deriving (Show, Read)
data ASTDatum = ASTSimpleDatum String | ASTLetDatum String deriving (Show, Read)
data AST = EmptyAST | ASTNode ASTDatum AST AST deriving (Show, Read)

isNumber :: String -> Bool
eagerEvaluation :: AST -> ASTResult
normalEvaluation :: AST -> ASTResult
-- DO NOT MODIFY OR DELETE THE LINES ABOVE --
-- IMPLEMENT isNumber, eagerEvaluation and normalEvaluation FUNCTIONS ACCORDING TO GIVEN SIGNATURES --

isNumber [] = False
isNumber [x] = elem x "0123456789"
isNumber (x:xs) = (checkLine x) && (checkDigits xs)

checkLine :: Char -> Bool
checkLine x = elem x "-0123456789"

checkDigits :: String -> Bool
checkDigits [] = True
checkDigits (x:xs) = (elem x "0123456789") && checkDigits xs

getName :: AST -> String
getName EmptyAST = ""
getName (ASTNode (ASTLetDatum xs) _ _) = xs
getName (ASTNode (ASTSimpleDatum xs) _ _) = xs

getDatumName :: ASTDatum -> String
getDatumName (ASTSimpleDatum xs) = xs
getDatumName (ASTLetDatum xs) = xs

errorType :: String-> String -> String -> ASTResult
errorType xs left right
            | xs == "num" = ASTError ("the value '" ++ left ++ "' is not a number!")
            | xs == "plus" = let
                                leftType = if(left `elem` ["str","cat"]) then "str" else "num"
                                rightType = if(right `elem` ["str","cat"]) then "str" else "num"
                             in ASTError ("plus operation is not defined between " ++ leftType ++ " and " ++ rightType ++"!")

            | xs == "times" = let
                                leftType = if(left `elem` ["str","cat"]) then "str" else "num"
                                rightType = if(right `elem` ["str","cat"]) then "str" else "num"
                             in  ASTError ("times operation is not defined between " ++ leftType ++ " and " ++ rightType ++"!")
            | xs == "negate" = let
                                leftType = if(left `elem` ["str","cat"]) then "str" else "num"
                             in ASTError ("negate operation is not defined on " ++ leftType ++ "!")
            | xs == "cat" = let
                                leftType = if(left `elem` ["str","cat"]) then "str" else "num"
                                rightType = if(right `elem` ["str","cat"]) then "str" else "num"
                             in ASTError ("cat operation is not defined between " ++ leftType ++ " and " ++ rightType ++"!")
            | xs == "len" = let
                                leftType = if(left `elem` ["str","cat"]) then "str" else "num"
                             in ASTError ("len operation is not defined on " ++ leftType ++ "!")


invalidOp :: String -> String -> String -> Bool
invalidOp xs left right
            | xs == "num" = if(isNumber left) then True else False
            | xs == "plus" = if(left `elem` ["str","cat"] || right `elem` ["str","cat"]) then False else True
            | xs == "times" = if(left `elem` ["str","cat"] || right `elem` ["str","cat"]) then False else True
            | xs == "negate" = if(left `elem` ["str","cat"]) then False else True
            | xs == "cat" = if(left `elem` ["len","num","negate","plus","times"] || right `elem` ["len","num","negate","plus","times"]) then False else True
            | xs == "len" = if(left `elem` ["cat","str"]) then True else False
            | otherwise = True

isValid :: AST -> Bool
isValid EmptyAST = True
isValid (ASTNode datum left right) = case datum of
                                                  (ASTLetDatum operation) -> isValid left && isValid right
                                                  (ASTSimpleDatum operation) -> (invalidOp operation (getName left) (getName right)) && isValid left && isValid right

detectingValid :: AST -> ASTResult
detectingValid (ASTNode datum left right) = if(isValid left == False)
                                              then detectingValid left
                                            else if(invalidOp (getDatumName datum) (getName left) (getName right) == False)
                                              then errorType (getDatumName datum) (getName left) (getName right)
                                            else
                                                detectingValid right

eagerEvaluation xs = if(isValid xs == False) then detectingValid xs else  (let replaced = replaceEagerAST xs
                                                                          in if(isValid replaced == False) then detectingValid replaced else ASTJust (evaluation replaced,takeType replaced,count xs))

replaceEagerAST :: AST -> AST
replaceEagerAST EmptyAST = EmptyAST
replaceEagerAST (ASTNode (ASTLetDatum x) left right) = let replaced = replaceEagerAST left
                                                                  in replaceHelper x (replaceEagerAST right) (ASTNode (ASTSimpleDatum (takeType replaced)) (ASTNode (ASTSimpleDatum (evaluation replaced)) EmptyAST EmptyAST) EmptyAST)
replaceEagerAST (ASTNode (ASTSimpleDatum x) left right) = (ASTNode (ASTSimpleDatum x) (replaceEagerAST left) (replaceEagerAST right))


-- NORMAL KISMI TAMAM
replaceAST :: AST -> AST
replaceAST EmptyAST = EmptyAST
replaceAST (ASTNode (ASTLetDatum x) left right) = replaceHelper x (replaceAST right)  (replaceAST left)
replaceAST (ASTNode (ASTSimpleDatum x) left right) = (ASTNode (ASTSimpleDatum x) (replaceAST left) (replaceAST right))


replaceHelper :: String -> AST -> AST -> AST
replaceHelper _ EmptyAST _ = EmptyAST
replaceHelper _ ((ASTNode (ASTLetDatum y) left right)) _ = (ASTNode (ASTLetDatum y) left right)
replaceHelper string (ASTNode datum left right) replace = if((getDatumName datum) == string) then replace
                                                          else (ASTNode datum (replaceHelper string left replace) (replaceHelper string right replace))


normalEvaluation xs = if(isValid xs == False) then detectingValid xs else (let replaced = replaceAST xs
                                                                                              in if(isValid replaced == False) then detectingValid replaced else ASTJust (evaluation replaced,takeType replaced,count replaced))

takeType :: AST -> String
takeType (ASTNode datum _ _) = if((getDatumName datum) `elem` ["plus","times","negate","len","num"]) then "num" else "str"

count :: AST -> Int
count EmptyAST = 0
count (ASTNode (ASTSimpleDatum x) left right) = if(x `elem` ["cat","len","times","plus","negate"]) then (1 + (count left) + (count right)) else ((count left) + (count right))
count (ASTNode (ASTLetDatum x) left right) = count left + count right

evaluation :: AST -> String
evaluation (ASTNode (ASTSimpleDatum x) EmptyAST EmptyAST) = x
evaluation (ASTNode (ASTSimpleDatum x) left right)
          | x == "plus" = show ((read (evaluation left)) + (read (evaluation right)))
          | x == "times" = show ((read (evaluation left)) * read ((evaluation right)))
          | x == "negate" = show (negate (read (evaluation left)))
          | x == "cat" = (evaluation left) ++ (evaluation right)
          | x == "len" = show (length (evaluation left))
          | x == "num" = (evaluation left)
          | x == "str" = (evaluation left)
