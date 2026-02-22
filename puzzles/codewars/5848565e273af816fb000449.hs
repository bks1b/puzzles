module SimpleEncryption where

import Data.Maybe (fromJust)
import Data.List (uncons)
import Control.Applicative (liftA2)
import Control.Arrow ((***))

encryptThis = unwords . map (uncurry (++) . (show . fromEnum
    *** maybe [] (uncurry $ (. uncons)
        . (. maybe [] (liftA2 (:) last init . uncurry (:)))
        . flip (++)
        . (: []))
    . uncons) . fromJust . uncons) . words