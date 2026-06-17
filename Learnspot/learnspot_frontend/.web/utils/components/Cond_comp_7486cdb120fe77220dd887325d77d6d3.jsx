
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_7486cdb120fe77220dd887325d77d6d3 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state)



    return(
        ((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.active_conv_id_rx_state_?.valueOf?.() === 0?.valueOf?.())?(children?.at?.(0)):(children?.at?.(1)))
    )
});
