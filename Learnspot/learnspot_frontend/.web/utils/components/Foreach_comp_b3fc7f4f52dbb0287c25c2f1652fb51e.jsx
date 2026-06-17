
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {Box as RadixThemesBox,Text as RadixThemesText} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Foreach_comp_b3fc7f4f52dbb0287c25c2f1652fb51e = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state.original_examples_rx_state_ ?? [],((ex_rx_state_,index_5fa831ce403e4003b74761cce1bf607b)=>(jsx(RadixThemesBox,{css:({ ["padding"] : "0.6rem 0.875rem", ["borderLeft"] : "2px solid #01696f", ["background"] : "rgba(1,105,111,0.04)", ["borderRadius"] : "0 0.4rem 0.4rem 0" }),key:index_5fa831ce403e4003b74761cce1bf607b},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.85rem", ["color"] : "#28251d", ["lineHeight"] : "1.55" })},ex_rx_state_)))))
    )
});
