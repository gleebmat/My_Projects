
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_7f9775183a2119fc05b779d9abef1479 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state)



    return(
        (!((reflex___state____state__learnspot___state___auth____auth_state.token_rx_state_?.valueOf?.() === ""?.valueOf?.()))?(children?.at?.(0)):(children?.at?.(1)))
    )
});
