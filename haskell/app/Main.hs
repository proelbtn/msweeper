module Main where

import Lib

main :: IO ()
main = do
    params <- getParameters
    let states = initMap params
    print states 