
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_d59febc60d30d08600e96c875d201706 = memo(({children}) => {
    const on_click_fe24fac5fdaea68e258f05eddb7426ac = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.new_conversation", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),onClick:on_click_fe24fac5fdaea68e258f05eddb7426ac,size:"2",variant:"soft"},children)
    )
});
