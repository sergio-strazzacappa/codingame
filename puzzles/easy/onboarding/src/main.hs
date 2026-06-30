import System.IO

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering

    loop

loop :: IO ()
loop = do
    inputLine <- getLine
    let enemy1 = inputLine :: String

    inputLine <- getLine
    let dist1 = read inputLine :: Int

    inputLine <- getLine
    let enemy2 = inputLine :: String

    inputLine <- getLine
    let dist2 = read inputLine :: Int

    if (dist1 < dist2)
        then putStrLn enemy1
        else putStrLn enemy2

    loop
