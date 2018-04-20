module Main where

import Lib

import System.Random.Shuffle

main :: IO ()
main = do
    params <- getParameters
    states <- initMap params
    result <- msweeper states
    print result