
import {Fragment,memo,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Box as RadixThemesBox} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Box_box_ffb87bb52d8eef4ac65d7280567ba170 = memo(({children}) => {
    
                useEffect(() => {
                    ((...args) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.load_conversations", ({  }), ({  })))], args, ({  }))))()
                    return () => {
                        
                    }
                }, []);



    return(
        jsx(RadixThemesBox,{css:({ ["width"] : "230px", ["minWidth"] : "230px", ["height"] : "calc(100vh - 58px)", ["background"] : "#f9f8f5", ["borderRight"] : "1px solid #e2e0db", ["overflow"] : "hidden", ["flexDirection"] : "column" })},children)
    )
});
