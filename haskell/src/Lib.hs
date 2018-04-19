module Lib (
    MSParams,
    MSMap,
    MSStates,
    MSCoords,
    getInteger,
    getParameters,
    getCoordinates,
    initMap
    ) where

import System.IO

type MSParams = (Int, Int, Int)
type MSMap = [Bool]
type MSStates = (MSParams, MSMap, MSMap)
type MSCoords = (Int, Int)

getInteger :: String -> IO Int
getInteger text = do
    putStr text
    hFlush stdout
    input <- getLine
    return (read input :: Int)

getParameters :: IO MSParams
getParameters = do
    width <- getInteger "Width : "
    height <- getInteger "Height : "
    bnum <- getInteger "Bomb : "
    return (width, height, bnum)

getCoordinates :: IO MSCoords
getCoordinates = do
    x <- getInteger "X : "
    y <- getInteger "Y : "
    return (x, y)

initMap :: MSParams -> MSStates
initMap params = (params, opened, bomb) 
    where
        (width, height, bnum) = params
        opened = map (== 0) [1..width * height]
        bomb = map (<= bnum) [1..width * height]
