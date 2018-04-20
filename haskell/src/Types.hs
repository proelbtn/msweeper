module Types (
    MSParams,
    MSMap,
    MSStates,
    MSCoords,
    ) where

type MSParams = (Int, Int, Int)
type MSMap = [Bool]
type MSStates = (MSParams, MSMap, MSMap)
type MSCoords = (Int, Int)