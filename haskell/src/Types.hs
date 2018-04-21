module Types (
    MSParams,
    MSMap,
    MSStates,
    MSCoords,
    MSResult
    ) where

type MSParams = (Int, Int, Int)
type MSMap = [Bool]
type MSStates = (MSParams, MSMap, MSMap)
type MSCoords = (Int, Int)

type MSResult = Bool