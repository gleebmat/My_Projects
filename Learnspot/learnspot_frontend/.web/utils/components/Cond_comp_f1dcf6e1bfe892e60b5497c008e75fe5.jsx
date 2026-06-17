
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Cond_comp_f1dcf6e1bfe892e60b5497c008e75fe5 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state)



    return(
        ((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state.translations_rx_state_.length > 0)?(children?.at?.(0)):(children?.at?.(1)))
    )
});
