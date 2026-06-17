
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {Badge as RadixThemesBadge} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Foreach_comp_588bea7d4f1d65c88c3fb5f35cf213a0 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state.translations_rx_state_ ?? [],((t_rx_state_,index_a5e1a725d11b03436e0aeabd80e8eef7)=>(jsx(RadixThemesBadge,{color:"teal",css:({ ["fontSize"] : "0.9rem", ["padding"] : "0.3rem 0.75rem" }),key:index_a5e1a725d11b03436e0aeabd80e8eef7,variant:"soft"},t_rx_state_))))
    )
});
