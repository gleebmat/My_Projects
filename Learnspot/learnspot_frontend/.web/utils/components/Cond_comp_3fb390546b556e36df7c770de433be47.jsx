
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_3fb390546b556e36df7c770de433be47 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state)



    return(
        (reflex___state____state__learnspot___state___auth____auth_state.loading_rx_state_?(children?.at?.(0)):(children?.at?.(1)))
    )
});
