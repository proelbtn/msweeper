module Lib (
    getInteger,
    getParameters,
    getCoordinates,
    initMap,
    msweeper
    ) where

import System.IO
import Types
import System.Random.Shuffle

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

initMap :: MSParams -> IO MSStates
initMap params = do
    let (width, height, bnum) = params
    let opened = replicate (width * height) False
    bomb <- shuffleM $ map (<= bnum) $ take (width * height) [1..]
    return (params, opened, bomb)

displayMap :: MSStates -> IO ()
displayMap states = do
    print "a"

isGameEnd :: MSStates -> Bool
isGameEnd states = True

getNextStates :: MSCoords -> MSStates -> MSStates
getNextStates coords states = states

getGameResults :: MSStates -> MSResult
getGameResults states = True

msweeper :: MSStates -> IO (MSResult)
msweeper states = do
    displayMap states
    coords <- getCoordinates
    let nstates = getNextStates coords states
    if isGameEnd nstates
        then return $ getGameResults nstates
        else msweeper nstates
        