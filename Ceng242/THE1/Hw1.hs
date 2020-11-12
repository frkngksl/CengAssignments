module Hw1 where

type Mapping = [(String, String, String)]
data AST = EmptyAST | ASTNode String AST AST deriving (Show, Read)

writeExpression :: (AST, Mapping) -> String
evaluateAST :: (AST, Mapping) -> (AST, String)
-- DO NOT MODIFY OR DELETE THE LINES ABOVE --
-- IMPLEMENT writeExpression and evaluateAST FUNCTION ACCORDING TO GIVEN SIGNATURES --

writeExpression (x,y) = mappingHelper y ++ operationChoose x

getName :: (String,String,String) -> String
getName (x,_,_) = x

getType :: (String,String,String) -> String
getType (_,y,_) = y

getValue :: (String,String,String) -> String
getValue (_,_,z) = z

mappingHelper :: Mapping -> String
mappingHelper x = if (length x == 1) then (keywordChoose1 x)
                  else (keywordChoose x 1)

keywordChoose1 :: Mapping -> String
keywordChoose1 [x]
            | (getType x) == "num" = "let " ++ (getName x) ++ "=" ++ (getValue x) ++ " in "
            | (getType x) == "str" = "let " ++ (getName x) ++ "=\"" ++ (getValue x) ++ "\" in "
            | otherwise = "Error"


keywordChoose :: Mapping -> Integer -> String
keywordChoose [] _ = ""
keywordChoose [x] y
            | (getType x) == "num" = (getName x) ++ "=" ++ (getValue x) ++ " in "
            | otherwise = (getName x) ++ "=\"" ++ (getValue x) ++ "\" in "
keywordChoose (x:xs) y
            | ((getType x) == "num" && y == 1) = "let " ++ (getName x) ++ "=" ++ (getValue x) ++ ";" ++ (keywordChoose xs 0)
            | ((getType x) == "num" && y == 0) = (getName x) ++ "=" ++ (getValue x) ++ ";" ++ (keywordChoose xs y)
            | ((getType x) == "str" && y == 1) = "let " ++ (getName x) ++ "=\"" ++ (getValue x) ++ "\";" ++ (keywordChoose xs 0)
            | ((getType x) == "str" && y == 0) = (getName x) ++ "=\"" ++ (getValue x) ++ "\";" ++ (keywordChoose xs y)
            | otherwise = "Error"

operationChoose :: AST -> String
operationChoose EmptyAST = ""
operationChoose (ASTNode x EmptyAST EmptyAST) = x
operationChoose (ASTNode x left right)
            | x == "plus" = "(" ++ (operationChoose left) ++ "+" ++ (operationChoose right) ++ ")"
            | x == "times" = "(" ++ (operationChoose left) ++ "*" ++ (operationChoose right) ++ ")"
            | x == "negate" = "(-" ++ (operationChoose left) ++ ")"
            | x == "cat" = "(" ++ (operationChoose left) ++ "++" ++ (operationChoose right) ++ ")"
            | x == "len" = "(length " ++ (operationChoose left) ++ ")"
            | x == "num" = operationChoose left
            | x == "str" =  "\"" ++ operationChoose left ++ "\""
            | otherwise = x
-- 40 puan tamam

isMap :: String -> Bool
isMap x = if (x `elem` ["plus","times","negate","cat","len","num","str"])
                        then False
                        else True

findValue :: String -> Mapping -> String
findValue _ [] = ""
findValue y (x:xs)
            | (y == (getName x)) = (getValue x)
            | otherwise = findValue y xs

findType :: String -> Mapping -> String
findType _ [] = ""
findType y (x:xs)
            | (y == (getName x)) = (getType x)
            | otherwise = findType y xs

replaceAST :: (AST,Mapping) -> AST
replaceAST (x,[]) = x
replaceAST (EmptyAST,_) = EmptyAST
replaceAST (ASTNode x left right,y)
          | x == "num" = (ASTNode x left right)
          | x == "str" = (ASTNode x left right)
          | (isMap x) = (ASTNode (findType x y) (ASTNode (findValue x y) EmptyAST EmptyAST) EmptyAST)
          | otherwise = (ASTNode x (replaceAST (left,y)) (replaceAST (right,y)))

evaluateAST (x,y) =
        let  replace = replaceAST (x,y)
             result = evaluation replace
        in   (replace,result)

evaluation :: AST -> String
evaluation (ASTNode x EmptyAST EmptyAST) = x
evaluation (ASTNode x left right)
          | x == "plus" = show ((read (evaluation left)) + (read (evaluation right)))
          | x == "times" = show ((read (evaluation left)) * read ((evaluation right)))
          | x == "negate" = show (negate (read (evaluation left)))
          | x == "cat" = (evaluation left) ++ (evaluation right)
          | x == "len" = show (length (evaluation left))
          | x == "num" = (evaluation left)
          | x == "str" = (evaluation left)
