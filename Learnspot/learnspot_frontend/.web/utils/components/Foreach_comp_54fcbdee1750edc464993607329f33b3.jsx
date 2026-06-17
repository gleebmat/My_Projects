
import {Fragment,memo,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {StateContexts,addEvents} from "$/utils/context"
import {Box as RadixThemesBox,Button as RadixThemesButton,Flex as RadixThemesFlex,Text as RadixThemesText} from "@radix-ui/themes"
import LucideEyeOff from "lucide-react/dist/esm/icons/eye-off.mjs"
import LucideEye from "lucide-react/dist/esm/icons/eye.mjs"
import {jsx} from "@emotion/react"






export const Foreach_comp_54fcbdee1750edc464993607329f33b3 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.quiz_questions_rx_state_ ?? [],((q_rx_state_,i_rx_state_)=>(jsx(RadixThemesBox,{css:({ ["padding"] : "1.1rem 1.25rem", ["background"] : "white", ["border"] : "1px solid #e2e0db", ["borderRadius"] : "0.75rem", ["boxShadow"] : "0 1px 4px rgba(0,0,0,0.04)", ["transition"] : "all 180ms ease", ["&:hover"] : ({ ["boxShadow"] : "0 4px 16px rgba(0,0,0,0.08)" }), ["width"] : "100%" }),key:i_rx_state_},jsx(RadixThemesFlex,{align:"start",className:"rx-Stack",css:({ ["width"] : "100%" }),direction:"column",gap:"3"},jsx(RadixThemesFlex,{align:"start",className:"rx-Stack",css:({ ["width"] : "100%" }),direction:"row",gap:"3"},jsx(RadixThemesBox,{css:({ ["background"] : "#01696f", ["width"] : "26px", ["height"] : "26px", ["borderRadius"] : "99px", ["display"] : "flex", ["alignItems"] : "center", ["justifyContent"] : "center", ["flexShrink"] : "0" })},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.75rem", ["fontWeight"] : "800", ["color"] : "white" })},q_rx_state_?.["number"])),jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.9rem", ["fontWeight"] : "600", ["color"] : "#1a1917", ["lineHeight"] : "1.4" })},q_rx_state_?.["task"])),jsx(Fragment,{},(!((q_rx_state_?.["text"]?.valueOf?.() === ""?.valueOf?.()))?(jsx(Fragment,{},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.85rem", ["color"] : "#7a7974", ["lineHeight"] : "1.55" })},q_rx_state_?.["text"]))):(jsx(Fragment,{},)))),jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),onClick:((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.toggle_answer", ({ ["index"] : i_rx_state_ }), ({  })))], [_e], ({  })))),size:"1",variant:"ghost"},jsx(Fragment,{},(isTrue(q_rx_state_?.["show_answer"])?(jsx(Fragment,{},jsx(RadixThemesFlex,{align:"start",className:"rx-Stack",direction:"row",gap:"1"},jsx(LucideEyeOff,{size:13},),jsx(RadixThemesText,{as:"p"},"Hide answer")))):(jsx(Fragment,{},jsx(RadixThemesFlex,{align:"start",className:"rx-Stack",direction:"row",gap:"1"},jsx(LucideEye,{size:13},),jsx(RadixThemesText,{as:"p"},"Show answer"))))))),jsx(Fragment,{},(isTrue(q_rx_state_?.["show_answer"])?(jsx(Fragment,{},jsx(RadixThemesBox,{css:({ ["padding"] : "0.75rem 1rem", ["background"] : "rgba(1,105,111,0.05)", ["border"] : "1px solid rgba(1,105,111,0.18)", ["borderRadius"] : "0.5rem", ["width"] : "100%" })},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.875rem", ["color"] : "#28251d", ["lineHeight"] : "1.65" })},q_rx_state_?.["answer"])))):(jsx(Fragment,{},)))))))))
    )
});
