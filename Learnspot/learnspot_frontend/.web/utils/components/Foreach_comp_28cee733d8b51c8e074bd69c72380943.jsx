
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {ColorModeContext,StateContexts} from "$/utils/context"
import {Box as RadixThemesBox,Code as RadixThemesCode,Flex as RadixThemesFlex,Heading as RadixThemesHeading,Link as RadixThemesLink,Text as RadixThemesText} from "@radix-ui/themes"
import ReactMarkdown from "react-markdown"
import remarkMath from "remark-math"
import remarkGfm from "remark-gfm"
import rehypeKatex from "rehype-katex"
import "katex/dist/katex.min.css"
import rehypeRaw from "rehype-raw"
import rehypeUnwrapImages from "rehype-unwrap-images"
import {Link as ReactRouterLink} from "react-router"
import {PrismAsyncLight as SyntaxHighlighter} from "react-syntax-highlighter"
import oneLight from "react-syntax-highlighter/dist/esm/styles/prism/one-light"
import oneDark from "react-syntax-highlighter/dist/esm/styles/prism/one-dark"
import {jsx} from "@emotion/react"




        function ComponentMap_d8b2dcef1196f2645c614da09ad39de0 () {
            const { resolvedColorMode } = useContext(ColorModeContext)



            return (
                ({ ["h1"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h1",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"6",...props},children))), ["h2"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h2",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"5",...props},children))), ["h3"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h3",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"4",...props},children))), ["h4"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h4",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"3",...props},children))), ["h5"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h5",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"2",...props},children))), ["h6"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h6",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"1",...props},children))), ["p"] : (({node, children, ...props}) => (jsx(RadixThemesText,{as:"p",css:({ ["marginTop"] : "1em", ["marginBottom"] : "1em" }),...props},children))), ["ul"] : (({node, children, ...props}) => (jsx("ul",{css:({ ["listStyleType"] : "disc", ["marginTop"] : "1em", ["marginBottom"] : "1em", ["marginLeft"] : "1.5rem", ["direction"] : "column" }),...props},children))), ["ol"] : (({node, children, ...props}) => (jsx("ol",{css:({ ["listStyleType"] : "decimal", ["marginTop"] : "1em", ["marginBottom"] : "1em", ["marginLeft"] : "1.5rem", ["direction"] : "column" }),...props},children))), ["li"] : (({node, children, ...props}) => (jsx("li",{css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),...props},children))), ["a"] : (({node, children, ...props}) => (jsx(RadixThemesLink,{css:({ ["&:hover"] : ({ ["color"] : "var(--accent-8)" }) }),href:"#",...props},children))), ["code"] : (({node, children, ...props}) => (jsx(RadixThemesCode,{...props},children))), ["pre"] : (({node, ...rest}) => { const {node: childNode, className, children: components, ...props} = rest.children.props; const children = String(Array.isArray(components) ? components.join('\n') : components).replace(/\n$/, ''); const match = (className || '').match(/language-(?<lang>.*)/); let _language = match ? match[1] : ''; ;             return jsx(SyntaxHighlighter,{children:children,css:({ ["marginTop"] : "1em", ["marginBottom"] : "1em" }),language:_language,style:((resolvedColorMode?.valueOf?.() === "light"?.valueOf?.()) ? oneLight : oneDark),wrapLongLines:true,...props},);         }) })
            )
        }
        


export const Foreach_comp_28cee733d8b51c8e074bd69c72380943 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.messages_rx_state_ ?? [],((msg_rx_state_,index_a8e8ac7006b71af63d9454b79c143665)=>(jsx(RadixThemesFlex,{css:({ ["width"] : "100%", ["paddingInlineStart"] : "1rem", ["paddingInlineEnd"] : "1rem" }),justify:((msg_rx_state_?.["role"]?.valueOf?.() === "user"?.valueOf?.()) ? "end" : "start"),key:index_a8e8ac7006b71af63d9454b79c143665},jsx(RadixThemesBox,{css:({ ["background"] : ((msg_rx_state_?.["role"]?.valueOf?.() === "user"?.valueOf?.()) ? "#01696f" : "white"), ["color"] : ((msg_rx_state_?.["role"]?.valueOf?.() === "user"?.valueOf?.()) ? "white" : "#28251d"), ["border"] : ((msg_rx_state_?.["role"]?.valueOf?.() === "user"?.valueOf?.()) ? "1px solid #01696f" : "1px solid #e2e0db"), ["borderRadius"] : ((msg_rx_state_?.["role"]?.valueOf?.() === "user"?.valueOf?.()) ? "1rem 1rem 0.25rem 1rem" : "1rem 1rem 1rem 0.25rem"), ["padding"] : "0.75rem 1rem", ["maxWidth"] : "70%", ["boxShadow"] : "0 1px 3px rgba(0,0,0,0.06)" })},jsx("div",{css:({ ["fontSize"] : "0.9rem", ["lineHeight"] : "1.65", ["color"] : "#28251d" })},jsx(ReactMarkdown,{components:ComponentMap_d8b2dcef1196f2645c614da09ad39de0(),rehypePlugins:[rehypeKatex, rehypeRaw, rehypeUnwrapImages],remarkPlugins:[remarkMath, remarkGfm]},msg_rx_state_?.["content"])))))))
    )
});
