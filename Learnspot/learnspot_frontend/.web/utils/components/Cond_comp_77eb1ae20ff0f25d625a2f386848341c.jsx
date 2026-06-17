
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_77eb1ae20ff0f25d625a2f386848341c = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        (!((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.practice_error_rx_state_?.valueOf?.() === ""?.valueOf?.()))?(children?.at?.(0)):(children?.at?.(1)))
    )
});
