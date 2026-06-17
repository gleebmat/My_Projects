
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_192cdc4f34056e330895e5c8ed753353 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state)



    return(
        (!((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state.improved_text_rx_state_?.valueOf?.() === ""?.valueOf?.()))?(children?.at?.(0)):(children?.at?.(1)))
    )
});
