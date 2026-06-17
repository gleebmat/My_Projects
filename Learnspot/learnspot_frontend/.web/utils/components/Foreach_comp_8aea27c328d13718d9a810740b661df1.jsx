
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {Box as RadixThemesBox,Text as RadixThemesText} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Foreach_comp_8aea27c328d13718d9a810740b661df1 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state.mistakes_rx_state_ ?? [],((m_rx_state_,index_a836606a63ef1f2afd77c06c6489b746)=>(jsx(RadixThemesBox,{css:({ ["padding"] : "0.6rem 0.875rem", ["borderLeft"] : "2px solid #a13544", ["background"] : "rgba(161,53,68,0.04)", ["borderRadius"] : "0 0.4rem 0.4rem 0" }),key:index_a836606a63ef1f2afd77c06c6489b746},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.85rem", ["color"] : "#28251d", ["lineHeight"] : "1.55" })},m_rx_state_)))))
    )
});
