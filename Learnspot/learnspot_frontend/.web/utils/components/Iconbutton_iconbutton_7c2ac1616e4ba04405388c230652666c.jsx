
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {IconButton as RadixThemesIconButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Iconbutton_iconbutton_7c2ac1616e4ba04405388c230652666c = memo(({children}) => {
    const on_click_fe24fac5fdaea68e258f05eddb7426ac = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.new_conversation", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesIconButton,{color:"teal",css:({ ["padding"] : "6px", ["cursor"] : "pointer" }),onClick:on_click_fe24fac5fdaea68e258f05eddb7426ac,size:"1",title:"New conversation",variant:"soft"},children)
    )
});
