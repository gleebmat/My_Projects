
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_cefbceb8403e35cdadd4cbca24a335bf = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        ((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.words_rx_state_.length > 0)?(children?.at?.(0)):(children?.at?.(1)))
    )
});
