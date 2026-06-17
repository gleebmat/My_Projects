
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {IconButton as RadixThemesIconButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Iconbutton_iconbutton_a286ad50bb069263caace0c2dea901db = memo(({children}) => {
    const on_click_095ad90aa9b3e52dbbf099231d20e8b3 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.send_message", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesIconButton,{color:"teal",css:({ ["padding"] : "6px", ["cursor"] : "pointer" }),onClick:on_click_095ad90aa9b3e52dbbf099231d20e8b3,size:"3",title:"Send"},children)
    )
});
